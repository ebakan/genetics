/*
 *  Algo.hpp
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

#ifndef ALGO_HPP
#define ALGO_HPP

#include <string>
#include <vector>

/**
 * Extremely generic interface for a genetic algorithm
 * initialize() and finalize() functions are guaranteed to be called by the
 * Processsor before and after Algo evaluation
 **/

class Algo
{
    public:
        virtual void initialize() = 0;
        virtual std::vector<double> update(const std::vector<double>& inputs)  = 0;
        virtual void finalize() = 0;
        virtual Algo* gen() const = 0;
        virtual std::string getSummary() const = 0;
};
#endif // ALGO_HPP
