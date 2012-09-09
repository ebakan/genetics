/*
 *  PDParam.cpp
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

#include "PDParam.hpp"

#include "rand.h"

PDParam::PDParam(double p, double k)
    : m_p(p)
    , m_k(k)
{
}

Param<double>* PDParam::gen() const
{
    if(m_k == 0)
    {
        return new PDParam(m_p, 0);
    }
    double p = m_p;
    if (p == 0)
    {
        p = randf();
    }
    return new PDParam(randgauss(m_k*(p), p), m_k);
}

const double& PDParam::get() const
{
    return m_p;
}
