#ifndef SOLVER_H
#define SOLVER_H

#include "stdio.h"
#include "base.h"

/* base class that each type of solver inherits from */
class Solver {
  protected:
    const size_t DIM;
    reals_f *system;
    size_t steps_taken;
    real_t *vars;
    real_t *temp_vars;
    real_t dt;
    real_t time_elapsed;

    void set_dt(real_t step) { dt = step; };
    virtual bool advance_internal(void) = 0;

  public:
    bool advance_step(void);
    real_t time(void) const { return time_elapsed; };
    size_t steps(void) const { return steps_taken; };
    void print_stats(void);
    void print_diagnostics(void);

    Solver(
        const size_t _DIM,
        reals_f *_system,
        real_t *init_vars,
        real_t _dt
    );
    ~Solver(void);
};

/* classic RK4 solver (fourth order) */
class RungeKutta4 : public Solver {
  private:
    real_t **k;
    real_t **midpoints;
    bool advance_internal(void);

  public:
    RungeKutta4(
        const size_t _DIM,
        reals_f *_system,
        real_t *_vars,
        real_t _dt
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
        real_t (*_system)(real_t*),
        real_t *_vars,
        real_t _dt,
        const char *filename
    );
};

/* improved euler method (second order) */
class EulerImproved : public Solver {
  private:
    real_t *trials;
    bool advance_internal(void);

  public:
    EulerImproved(
        int _DIM,
        real_t (*_system)(real_t*),
        real_t *init_vars,
        real_t _dt,
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
