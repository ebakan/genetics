/*
 *  rand.c
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


#include "rand.h"

#include "gsl/gsl.h"

#include <stdio.h>
#include <time.h>

const gsl_rng_type* T;
gsl_rng* r;

double randf()
{
    return gsl_rng_uniform(r);
}

double randgauss(const double mu, const double sigma)
{
    return gsl_ran_gaussian_ziggurat(r,sigma)+mu;
}

void init_rng()
{
    gsl_rng_env_setup();
    T = gsl_rng_taus;
    r = gsl_rng_alloc(T);
    gsl_rng_set(r,time(NULL));
}

void free_rng()
{
    gsl_rng_free(r);
}

