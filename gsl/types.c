/* rng/types.c
 * 
 * Copyright (C) 2001, 2007 Brian Gough
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

//#include <config.h>
#include <stdlib.h>
#include "gsl.h"

#define N 100

const gsl_rng_type * gsl_rng_generator_types[N];

#define ADD(t) {if (i==N) abort(); gsl_rng_generator_types[i] = (t); i++; };

const gsl_rng_type **
gsl_rng_types_setup (void)
{
  int i = 0;

  ADD(gsl_rng_taus);
  ADD(0);

  return gsl_rng_generator_types;
}

