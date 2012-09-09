/*
 *  main.cpp
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

#include "God.hpp"
#include "PDParam.hpp"
#include "PID1DProcessor.hpp"
#include "PIDAlgo.hpp"
#include "rand.h"

#include <pthread.h>
#include <stdio.h>

/**
 * Main program
 * Simulates a 1D robot moving towards a goal
 * Uses a genetic algorithm to tune the PID control loop governing its motion
 */

int main(int argc, char** argv)
{
    init_rng();

    static const double timeout                     =   5.00;
    static const double timein                      =   1.00;
    static const double threshold                   =   0.01;
    static const double maxVoltage                  =  12.00;
    static const double minVoltage                  = -12.00;
    static const double goal                        =   1.00;
    static const double mass                        =  1.000;
    static const double motorStallTorque            = 010.00;
    static const double motorFreeSpeed              = 010.00;
    static const double gearingRatio                =   1.00;
    static const double wheelDiameter               =   0.03;
    static const double staticFriction              =   0.50;
    static const double kineticFriction             =   0.10;
    static const double seedKP                      =   0.00;
    static const double seedKI                      =   0.00;
    static const double seedKD                      =   0.00;
    static const double k                           =   1.00;

    static const unsigned int populationSize        =  4000;
    static const unsigned int successorSize         =    10;
    static const unsigned int minThreadWorkloadSize =   100;
    static const unsigned int maxNumThreads         =     8;
    static const unsigned int numCycles             =   100;

    PID1DProcessor processor(timeout, timein, threshold, maxVoltage, minVoltage, goal, mass, motorStallTorque, motorFreeSpeed, gearingRatio, wheelDiameter, staticFriction, kineticFriction);

    std::vector<Algo*> seeds(1);
    seeds[0] = new PIDAlgo(new PDParam(seedKP, k), new PDParam(seedKI, 0), new PDParam(seedKD, k/100.0), maxVoltage, minVoltage);


    God god(processor, seeds, populationSize, successorSize, minThreadWorkloadSize, maxNumThreads, numCycles);

    AlgoScore best = god.simulate<God::minScoreHeap, God::patientComplete>();

    printf("Winning Algo:\n");
    printf("%s",best.algo->getSummary().c_str());
    printf("Success: %d Score: %f\n", best.score.success, best.score.score);
    processor.process(best.algo, "winner.log");

    free_rng();

    pthread_exit(NULL);
}
