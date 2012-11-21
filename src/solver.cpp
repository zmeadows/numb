#include "solver.h"

/*
// BASIC EULER METHOD
Euler::Euler(int dim, func *eqns, const double *init_vars, double step, const char *filename)
    : Solver(dim, eqns, init_vars, step, filename) {}

void Euler::advance_internal(void) {
    int i;
    for (i=0;i<dimension;++i) {
        temp_vars[i] = vars[i] + equations[i](vars) * timestep;
    }
}

// IMPROVED EULER METHOD
EulerImproved::EulerImproved(int dim, func *eqns, const double *init_vars, double step, const char *filename)
    : Solver(dim, eqns, init_vars, step, filename),
      trials(new double[dim]) {}

EulerImproved::~EulerImproved(void) {
    delete trials;
}

void EulerImproved::advance_internal(void) {
    int i;
    for (i=0;i<dimension;++i) {
        trials[i] = vars[i] + equations[i](vars) * timestep;
    }
    for (i=0;i<dimension;++i) {
        temp_vars[i] = vars[i] + 0.5 * (equations[i](vars) + equations[i](trials)) * timestep;
    }
}
*/

// RUNGE KUTTA 4TH ORDER
// ADAPTIVE RUNGE KUTTA 4TH ORDER
// LEAPFROG METHOD
