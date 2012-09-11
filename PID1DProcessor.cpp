/*
 *  PID1DProcessor.cpp
 *  Copyright (C) 2012 Eric Bakan
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PID1DProcessor.hpp"

#include "Algo.hpp"

#include <math.h>
#include <fstream>
#include <vector>

PID1DProcessor::PID1DProcessor(double timeout, double timein, double threshold, double maxVoltage, double minVoltage, double goal, double mass, double motorStallTorque, double motorFreeSpeed, double gearingRatio, double wheelDiameter, double staticFriction, double kineticFriction)
    : m_timeout(timeout)
    , m_timein(timein)
    , m_threshold(threshold)
    , m_maxVoltage(maxVoltage)
    , m_minVoltage(minVoltage)
    , m_goal(goal)
    , m_mass(mass)
    , m_motorStallTorque(motorStallTorque)
    , m_motorFreeSpeed(motorFreeSpeed)
    , m_gearingRatio(gearingRatio)
    , m_wheelDiameter(wheelDiameter)
    , m_staticFriction(staticFriction)
    , m_kineticFriction(kineticFriction)
{
}

Processor::Score PID1DProcessor::process(Algo* a, std::string logname) const
{
    static const double dt = 1e-3; // 1ms

    std::ofstream* of = NULL;
    if (logname.size())
    {
        of = new std::ofstream(logname.c_str());
    }

    double theta = 0;
    double omega = 0;
    double alpha = 0;
    double t = 0;
    double steadytime = 0;
    double wheelCircumference = M_PI * m_wheelDiameter;
    double finalSpeed = m_motorFreeSpeed / m_gearingRatio;
    double inertia = m_mass; // Not entirely accurate, need to think harder
    double score = 0.0;
    std::vector<double> inputs(2);
    std::vector<double> output;
    while (t < m_timeout || (steadytime > 0  && steadytime < m_timein))
    {

        // Model for motor: http://www.inf.fu-berlin.de/lehre/SS05/Robotik/motors.pdf

        inputs[0] = m_goal;
        inputs[1] = theta * wheelCircumference;
        output = a->update(inputs);

        double stallTorque = m_motorStallTorque * output[0] / m_maxVoltage * m_gearingRatio;

        alpha = stallTorque / inertia * (1 - omega / finalSpeed);
        if (omega == 0)
        {
            if (fabs(alpha) < m_mass * m_staticFriction)
            {
                alpha = 0;
            }
        }
        else
        {
            if (alpha > 0)
            {
                alpha -= m_mass * m_kineticFriction;
                if (alpha < 0)
                {
                    alpha = 0;
                }
            }
            else if (alpha < 0)
            {
                alpha += m_mass * m_kineticFriction;
                if (alpha > 0)
                {
                    alpha = 0;
                }
            }
        }
        theta += omega * dt + 0.5 * alpha * dt * dt;
        omega += alpha * dt;

        double pos = theta * wheelCircumference;
        if (fabs(m_goal-pos) < m_threshold)
        {
            steadytime += dt;
        }
        else
        {
            steadytime = 0;
        }

        score += fabs(m_goal - pos) * dt;

        if (of)
        {
            *of << t << "," << theta << "," << omega << "," << alpha << "," << output[0] << "," << steadytime << "," << m_goal / wheelCircumference << "," << score << std::endl;
        }

        t += dt;
    }

    if (of)
    {
        of->close();
        delete of;
    }

    Processor::Score ret = {steadytime > 0, score};
    return ret;
}

