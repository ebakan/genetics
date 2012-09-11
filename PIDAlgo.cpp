/*
 *  PIDAlgo.cpp
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

#include "PIDAlgo.hpp"

#include <sstream>


PIDAlgo::PIDAlgo(Param<double>* kP, Param<double>* kI, Param<double>* kD, double maxPower, double minPower)
    : m_kP(kP)
    , m_kI(kI)
    , m_kD(kD)
    , m_maxPower(maxPower)
    , m_minPower(minPower)
{
}

PIDAlgo::~PIDAlgo()
{
    delete m_kP;
    delete m_kI;
    delete m_kD;
}

void PIDAlgo::initialize()
{
    m_errorSum = 0;
    m_lastError = 0;
}

std::vector<double> PIDAlgo::update(const std::vector<double>& inputs)
{
    double kP = m_kP->get();
    double kI = m_kI->get();
    double kD = m_kD->get();
    double error = inputs[0] - inputs[1];
    double p = kP * error;
    m_errorSum += error;
    if (m_errorSum * kI > m_maxPower)
    {
        m_errorSum = m_maxPower / kI;
    }
    else if (m_errorSum * kI < m_minPower)
    {
        m_errorSum = m_minPower / kI;
    }
    double i = kI * m_errorSum;
    double dError = error - m_lastError;
    double d = kD * dError;
    if (d > m_maxPower)
    {
        d = m_maxPower;
    }
    else if (d < m_minPower)
    {
        d = m_minPower;
    }
    m_lastError = error;

    double power =  p + i + d;

    std::vector<double> out(1);
    if (power > m_maxPower)
    {
        out[0] = m_maxPower;
    }
    else if (power < m_minPower)
    {
        out[0] = m_minPower;
    }
    else
    {
        out[0] = power;
    }
    return out;
}

void PIDAlgo::finalize()
{
    m_errorSum = 0;
    m_lastError = 0;
}

Algo* PIDAlgo::gen() const
{
    return new PIDAlgo(m_kP->gen(), m_kI->gen(), m_kD->gen(), m_maxPower, m_minPower);
}

std::string PIDAlgo::getSummary() const
{
    std::stringstream ss;
    ss << "kP: " << m_kP->get() << "kI: " << m_kI->get() << "kD: " << m_kD->get() << std::endl;
    return ss.str();
}
