#ifndef SOLVER_HXX
#define SOLVER_HXX

#include "solver.h"

/* solver base class */
Solver::Solver(
        const size_t _DIM,
        reals_f *_system,
        real_t *init_vars,
        real_t _dt
        )
: DIM(_DIM),
    system(_system),
    steps_taken(0),
    vars(new real_t[_DIM]),
    temp_vars(new real_t[_DIM]),
    dt(_dt),
    time_elapsed(0)
{
    size_t i;
    for (i = 0; i < DIM; ++i) {
        vars[i] = init_vars[i];
    }
}

Solver::~Solver(void) {
    delete vars;
    delete temp_vars;
}

bool Solver::advance_step(void) {

    if (!(advance_internal())) return false;
    time_elapsed += dt;
    ++steps_taken;

    size_t i;
    for (i = 0; i < DIM; ++i) {
        vars[i] = temp_vars[i];
    }

    return true;
}

void Solver::print_stats(void) {
    fprintf(stdout, "%.16g\t", time_elapsed);
    size_t i;
    for (i = 0; i < DIM; ++i) {
        fprintf(stdout, "%.16g\t", vars[i]);
    }
    fprintf(stdout, "\n");

}

void Solver::print_diagnostics(void) {
}

RungeKutta4::RungeKutta4(
        const size_t _DIM,
        reals_f *_system,
        real_t *_vars,
        real_t _dt
	    )
	    : Solver(_DIM, _system, _vars, _dt),
          k(new real_t*[4]),
          midpoints(new real_t*[3])
{
    for(int i = 0; i < 4; ++i) {
        k[i] = new real_t[_DIM];
    }
    for(int i = 0; i < 3; ++i) {
        midpoints[i] = new real_t[_DIM];
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

bool RungeKutta4::advance_internal(void) {

    size_t i;

    // k1
    for (i=0;i<DIM;++i) {
        k[0][i] = system[i](vars) * dt;
        midpoints[0][i] = vars[i] + 0.5 * k[0][i];
    }

    // k2
    for (i=0;i<DIM;++i) {
        k[1][i] = system[i](midpoints[0]) * dt;
        midpoints[1][i] = vars[i] + 0.5 * k[1][i];
    }

    // k3
    for (i=0;i<DIM;++i) {
        k[2][i] = system[i](midpoints[1]) * dt;
        midpoints[2][i] = vars[i] + k[2][i];
    }

    // k4
    for (i=0;i<DIM;++i) {
        k[3][i] = system[i](midpoints[2]) * dt;
    }

    for (i=0;i<DIM;++i) {
        temp_vars[i] = vars[i] +
            (1.0/6.0) * (k[0][i] + 2*k[1][i] + 2*k[2][i] + k[3][i]);
    }

    return true;
}

#endif
