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

#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>

class Algo;

/**
 * The fitness function to evaluate an algorithm
 * NOTE: All Processor implementations MUST call initialize() and finalize() on
 * each Algo before and after it is run, respectively
 * Additionally, process() must be guaranteed to be thread-safe for distributed
 * applications
 * Implementations of process() shall log select data to a textfile iff the length
 * of logname > 0
 */

class Processor
{
    public:
        struct Score {
            bool success;
            double score;
        };

        virtual Score process(Algo* a, std::string logname="") const = 0;
        
};

#endif //PROCESSOR_HPP
