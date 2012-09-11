/*
 *  PIDAlgo.hpp
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

#ifndef PID_ALGO_HPP
#define PID_ALGO_HPP

#include "Algo.hpp"
#include "PDParam.hpp"
/**
 * Genetic implementation of a PID control loop
 */

class PIDAlgo : public virtual Algo
{
    public:
        PIDAlgo(Param<double>* kP, Param<double>* kI, Param<double>* kD, double maxPower, double minPower);
        ~PIDAlgo();
        virtual void initialize();
        /**
         * @param inputs a 2-element vector of (goal, current)
         * @preturn a 1-element vector of (power)
         */
        virtual std::vector<double> update(const std::vector<double>& inputs);
        virtual void finalize();
        virtual Algo* gen() const;
        virtual std::string getSummary() const;
    private:
        PIDAlgo(const PIDAlgo& pidalgo);
        const PIDAlgo& operator=(const PIDAlgo& pidalgo);
        Param<double>* m_kP;
        Param<double>* m_kI;
        Param<double>* m_kD;
        double m_errorSum;
        double m_lastError;
        double m_maxPower;
        double m_minPower;
};
#endif // PID_ALGO_HPP
