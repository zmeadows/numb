#ifndef BASE_H
#define BASE_H

typedef double real_t;

/* real_f represents a function from reals to reals */
typedef double (*real_f)(double);

/* reals_f represents a function from R_n to R_1 */
typedef double (*reals_f)(double*);

/* system of ODE's */
typedef reals_f *ode_system;

#endif
