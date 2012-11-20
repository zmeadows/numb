#ifndef SOLVER_H
#define SOLVER_H

#include "stdio.h"
#include "base.h"

// base class that each type of solver inherits from
class Solver {
  protected:
    func *equations;
    int dimension;
    int steps_completed;
    double *vars;
    double *temp_vars;
    double timestep;
    double time_elapsed;
    FILE *log_file;
    bool log_output;
    bool debug;

    void advance(void);
    virtual void advance_internal(void) = 0;

  public:
    void solve(double duration);

    void set_timestep(double step) { timestep = step; };

    void start_logging(void) { log_output = true; };
    void stop_logging(void) { log_output = false; };

    void start_debugging(void) { debug = true; };
    void stop_debugging(void) { debug = false; };

    Solver(int dim, func *eqns, const double *init_vars, double step, const char *filename);
    ~Solver(void);
};

// classic RK4 solver (fourth order)
class RungeKutta4 : public Solver {
  private:
    double **k;
    double **midpoints;
    void advance_internal(void);

  public:
    RungeKutta4(int dim, func *eqns, const double *init_vars, double step, const char *filename);
    ~RungeKutta4(void);
};

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

/*
class RungeKutta4Adaptive : protected Solver {

};

class LeapFrog : protected Solver {

};

*/

#endif
