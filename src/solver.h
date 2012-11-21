#ifndef SOLVER_H
#define SOLVER_H

#include "stdio.h"
#include "base.h"
#include <algorithm>

// base class that each type of solver inherits from
template <class T>
class Solver {
  protected:
    func<T> *system;
    int dimension;
    int steps_completed;
    T *vars;
    T *temp_vars;
    T timestep;
    T time_elapsed;
    FILE *log_file;
    bool log_output;
    bool debug;

    void advance(void);
    virtual void advance_internal(void) = 0;

  public:
    void solve(T duration);

    void set_timestep(T step) { timestep = step; };

    void start_logging(void) { log_output = true; };
    void stop_logging(void) { log_output = false; };

    void start_debugging(void) { debug = true; };
    void stop_debugging(void) { debug = false; };

    Solver(
            int _dimension,
            func<T> *_system,
            T *init_vars,
            T _timestep,
            const char *filename
            );

    ~Solver(void);
};

// SOLVER BASE CLASS
template <class T>
Solver<T>::Solver(
        int _dimension,
        func<T> *_system,
        T *init_vars,
        T _timestep,
        const char *filename
    ):
    system(_system),
    dimension(_dimension),
    steps_completed(0),
    vars(new double[_dimension]),
    temp_vars(new double[_dimension]),
    timestep(_timestep),
    time_elapsed(0),
    log_output(true),
    debug(false)
{
    std::copy(init_vars,init_vars + dimension, vars);
    if (!(log_file = (fopen(filename, "w")))) {
        printf("numb: could not open file (%s)for logging", filename);
        log_output = false;
        debug = true;
    }
}

template <class T>
Solver<T>::~Solver(void) {
    delete vars;
    delete temp_vars;
    fclose(log_file);
}

template <class T>
void Solver<T>::advance(void) {
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
    if (debug) {

    }
}

template <class T>
void Solver<T>::solve(T duration) {
    while (time_elapsed < duration) {
        advance();
        if (debug) {
        }
    }
}



// classic RK4 solver (fourth order)
template <class T>
class RungeKutta4 : public Solver<T> {
  private:
    T **k;
    T **midpoints;
    void advance_internal(void);

  public:
    RungeKutta4(
            int _dimension,
            func<T> *_system,
            T *init_vars,
            T _timestep,
            const char *filename
            );

    ~RungeKutta4(void);
};

template <class T> RungeKutta4<T>::RungeKutta4(
        int _dimension,
        func<T> *_system,
        T *init_vars,
        T _timestep,
        const char *filename)
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

template <class T> RungeKutta4<T>::~RungeKutta4(void) {

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

template <class T> void RungeKutta4<T>::advance_internal(void) {

    int i;

    // k1
    for (i=0;i<this->dimension;++i) {
        k[0][i] = this->system[i](this->vars) * this->timestep;
        midpoints[0][i] = this->vars[i] + 0.5 * k[0][i];
    }

    // k2
    for (i=0;i<this->dimension;++i) {
        k[1][i] = this->system[i](midpoints[0]) * this->timestep;
        midpoints[1][i] = this->vars[i] + 0.5 * k[1][i];
    }

    // k3
    for (i=0;i<this->dimension;++i) {
        k[2][i] = this->system[i](midpoints[1]) * this->timestep;
        midpoints[2][i] = this->vars[i] + k[2][i];
    }

    // k4
    for (i=0;i<this->dimension;++i) {
        k[3][i] = this->system[i](midpoints[2]) * this->timestep;
    }

    for (i=0;i<this->dimension;++i) {
        this->temp_vars[i] = this->vars[i] + (1.0/6.0) * (k[0][i] + 2*k[1][i] + 2*k[2][i] + k[3][i]);
    }
}



/*
// straight foward euler method (first order)
class Euler : public Solver {
  private:
    void advance_internal(void);

  public:
    Euler(int dim, func *eqns, const double *init_vars, double step, const char *filename);
};

// improved euler method (second order)
class EulerImproved : public Solver {
  private:
    double *trials;
    void advance_internal(void);

  public:
    EulerImproved(int dim, func *eqns, const double *init_vars, double step, const char *filename);
    ~EulerImproved(void);
};

class RungeKutta4Adaptive : protected Solver {

};

class LeapFrog : protected Solver {

};

*/

#endif
