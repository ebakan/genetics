/*
 *  PDParam.hpp
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

#ifndef PD_PARAM_HPP
#define PD_PARAM_HPP

#include "Param.hpp"

/**
 * Proportional Double Param
 * Encapsulates a double data member and generates children from a gaussian
 * distribution with mu=current value and sigma=k*mu for some constant k
 **/

class PDParam : public virtual Param<double>
{
    public:
        PDParam(double p=0, double k=1);
        virtual Param<double>* gen() const;
        virtual const double& get() const;
    private:
        double m_p;
        double m_k;

};
#endif // PD_PARAM_HPP
