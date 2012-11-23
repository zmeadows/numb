#ifndef BASE_H
#define BASE_H

#include "stdlib.h"

typedef double real_t;

/* real_f represents a function from reals to reals */
typedef double (*real_f)(double);

/* reals_f represents a function from R_n to R_1 */
typedef double (*reals_f)(double*);

/* system of ODE's */
typedef reals_f *ode_system;

double rand_double(double min, double max);

real_t signum(real_t n);

#endif
