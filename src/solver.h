#ifndef SOLVER_H
#define SOLVER_H

#include "stdio.h"
#include "base.h"

/* base class that each type of solver inherits from */
class Solver {
  protected:
    const int DIM;
    ode_system system;
    int steps_taken;
    double *vars;
    double *temp_vars;
    double dt;
    double time_elapsed;

    void set_dt(double step) { dt = step; };
    virtual bool advance_internal(void) = 0;

  public:
    bool advance_step(void);
    double time(void) const { return time_elapsed; };
    int steps(void) const { return steps_taken; };
    void print_stats(void);
    void print_diagnostics(void);

    Solver(
        const int _DIM,
        ode_system _system,
        double *init_vars,
        double _dt
    );
    ~Solver(void);
};

/* classic RK4 solver (fourth order) */
class RungeKutta4 : public Solver {
  private:
    double **k;
    double **midpoints;
    bool advance_internal(void);

  public:
    RungeKutta4(
        const int _DIM,
        ode_system _system,
        double *_vars,
        double _dt
    );

    ~RungeKutta4(void);
};


/* straight foward Euler method (first order) */
class Euler : public Solver {
  private:
    bool advance_internal(void);

  public:
    Euler(
        int _DIM,
        ode_system _system,
        double *_vars,
        double _dt,
        const char *filename
    );
};

/* improved euler method (second order) */
class EulerImproved : public Solver {
  private:
    double *trials;
    bool advance_internal(void);

  public:
    EulerImproved(
        int _DIM,
        ode_system _system,
        double *init_vars,
        double _dt,
        const char *filename
    );
    ~EulerImproved(void);
};

/*
class RungeKutta4Adaptive : protected Solver {

};

class LeapFrog : protected Solver {

};

*/

#endif
