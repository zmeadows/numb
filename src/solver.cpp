#include "solver.h"
#include <algorithm>

// SOLVER BASE CLASS
Solver::Solver(int dim, func *eqns, const double *init_vars, double step, const char *filename)
  : equations(eqns),
    dimension(dim),
    steps_completed(0),
    vars(new double[dim]),
    temp_vars(new double[dim]),
    timestep(step),
    time_elapsed(0),
    log_file(fopen(filename, "w")),
    log_output(true),
    debug(false)
{
    std::copy(init_vars,init_vars + dimension, vars);
}

Solver::~Solver(void) {
    delete vars;
    delete temp_vars;
    fclose(log_file);
}

void Solver::advance(void) {
    advance_internal();
    time_elapsed += timestep;
    ++steps_completed;

    std::copy(temp_vars,temp_vars + dimension, vars);

    int i;
    if (log_output && steps_completed % 10 == 0) {
        fprintf(log_file, "%.9g ", time_elapsed);
        for (i=0;i<dimension;++i) {
            fprintf(log_file, "%.15g ", vars[i]);
        }
        fprintf(log_file, "\n");
        fflush (log_file);
    }
}

void Solver::solve(double duration) {
    while (time_elapsed < duration) { advance(); };

    if (debug) {
        // print some stats
    }
}

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

// RUNGE KUTTA 4TH ORDER
RungeKutta4::RungeKutta4(int dim, func *eqns, const double *init_vars, double step, const char *filename)
    : Solver(dim, eqns, init_vars, step, filename)
{
    k = new double*[4];
    midpoints = new double*[3];

    for(int i = 0; i < 4; ++i) {
        k[i] = new double[dim];
    }
    for(int i = 0; i < 3; ++i) {
        midpoints[i] = new double[dim];
    }
}

RungeKutta4::~RungeKutta4(void) {

    int i;
    for(i = 0; i < 4; ++i) {
        delete [] k[i];
    }
    for(i = 0; i < 3; ++i) {
        delete [] midpoints[i];
    }

    delete [] k;
    delete [] midpoints;
}

void RungeKutta4::advance_internal(void) {

    int i;

    // k1
    for (i=0;i<dimension;++i) {
        k[0][i] = equations[i](vars) * timestep;
        midpoints[0][i] = vars[i] + 0.5 * k[0][i];
    }

    // k2
    for (i=0;i<dimension;++i) {
        k[1][i] = equations[i](midpoints[0]) * timestep;
        midpoints[1][i] = vars[i] + 0.5 * k[1][i];
    }

    // k3
    for (i=0;i<dimension;++i) {
        k[2][i] = equations[i](midpoints[1]) * timestep;
        midpoints[2][i] = vars[i] + k[2][i];
    }

    // k4
    for (i=0;i<dimension;++i) {
        k[3][i] = equations[i](midpoints[2]) * timestep;
    }

    for (i=0;i<dimension;++i) {
        temp_vars[i] = vars[i] + (1.0/6.0) * (k[0][i] + 2*k[1][i] + 2*k[2][i] + k[3][i]);
    }
}

// ADAPTIVE RUNGE KUTTA 4TH ORDER
// LEAPFROG METHOD
