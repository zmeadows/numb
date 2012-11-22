#ifndef SOLVER_HXX
#define SOLVER_HXX

#include "solver.h"

// SOLVER BASE CLASS
Solver::Solver(
      uint _dimension,
      real_t (*_system)(real_t*),
      real_t *_vars,
      real_t _timestep,
      const char *filename
      ) 
      : system(_system),
	dimension(_dimension),
	steps_completed(0),
	vars(_vars),
	temp_vars(new T[_dimension]),
	timestep(_timestep),
	time_elapsed(0) 
	{  
	}

Solver::~Solver(void) {
    delete vars;
    delete temp_vars;
}

bool Solver::advance(void) {
    if (!(advance_internal())) return false;
    time_elapsed += timestep;
    ++steps_completed;

    std::copy(temp_vars,temp_vars + dimension, vars);

    return true;
}

RungeKutta4::RungeKutta4(
        int _dimension,
	real_t (*_system)(real_t*),
        real_t *init_vars,
        real_t _timestep,
        const char *filename
	)
	: Solver<T>(_dimension, _system, init_vars, _timestep, filename)
{
    k = new T*[4];
    midpoints = new T*[3];

    for(int i = 0; i < 4; ++i) {
        k[i] = new T[_dimension];
    }
    for(int i = 0; i < 3; ++i) {
        midpoints[i] = new T[_dimension];
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

    int i;

    // k1
    for (i=0;i<dimension;++i) {
        k[0][i] = system[i](vars) * timestep;
        midpoints[0][i] = vars[i] + 0.5 * k[0][i];
    }

    // k2
    for (i=0;i<dimension;++i) {
        k[1][i] = system[i](midpoints[0]) * timestep;
        midpoints[1][i] = vars[i] + 0.5 * k[1][i];
    }

    // k3
    for (i=0;i<dimension;++i) {
        k[2][i] = system[i](midpoints[1]) * timestep;
        midpoints[2][i] = vars[i] + k[2][i];
    }

    // k4
    for (i=0;i<dimension;++i) {
        k[3][i] = system[i](midpoints[2]) * timestep;
    }

    for (i=0;i<dimension;++i) {
        temp_vars[i] = vars[i] +
            (1.0/6.0) * (k[0][i] + 2*k[1][i] + 2*k[2][i] + k[3][i]);
    }
    
    return true;
}

#endif
