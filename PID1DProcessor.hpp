/*
 *  PID1DProcessor.hpp
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

#ifndef PID_1D_PROCESSOR_HPP
#define PID_1D_PROCESSOR_HPP

#include "Processor.hpp"

#include <pthread.h>

/**
 * Simulation of a robot moving in 1D
 * Uses SI mks units
 * Const private data members are immutable and don't need a thread lock (I think?)
 */
class PID1DProcessor : public virtual Processor
{
    public:
        PID1DProcessor(double timeout, double timein, double threshold, double maxVoltage, double minVoltage, double goal, double mass, double motorStallTorque, double motorFreeSpeed, double gearingRatio, double wheelDiameter, double staticFriction, double kineticFriction);
        virtual Processor::Score process(Algo* a, std::string logname="") const;
    private:
        const double m_timeout;
        const double m_timein;
        const double m_threshold;
        const double m_maxVoltage;
        const double m_minVoltage;
        const double m_goal;
        const double m_mass;
        const double m_motorStallTorque;
        const double m_motorFreeSpeed;
        const double m_gearingRatio;
        const double m_wheelDiameter;
        const double m_staticFriction;
        const double m_kineticFriction;
};

#endif // PID_1D_PROCESSOR_HPP
