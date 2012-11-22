#ifndef SOLVER_H
#define SOLVER_H

#include "stdio.h"
#include "base.h"

/* base class that each type of solver inherits from */
class Solver {
  protected:
    real_t (*system)(real_t*);
    uint dimension;
    uint steps_completed;
    real_t *vars;
    real_t *temp_vars;
    real_t timestep;
    real_t time_elapsed;

    virtual bool advance_internal(void) = 0;

  public:
    bool advance(void);
    real_t time_elapsed (void) const {
        return time_elapsed;
    };
    void set_timestep(real_t step) {
        timestep = step;
    };

    Solver(
        int _dimension,
        real_t (*_system)(real_t*),
        real_t *_vars,
        real_t _timestep,
        const char *filename
    );

    ~Solver(void);
};

/* classic RK4 solver (fourth order) */
class RungeKutta4 : protected Solver {
  private:
    real_t **k;
    real_t **midpoints;
    bool advance_internal(void);

  public:
    RungeKutta4(
        int _dimension,
        real_t (*_system)(real_t*),
        real_t *_vars,
        real_t _timestep,
        const char *filename
    );

    ~RungeKutta4(void);
};


/* straight foward Euler method (first order) */
class Euler : protected Solver {
  private:
    void advance_internal(void);

  public:
    Euler(
        int _dimension,
        real_t (*_system)(real_t*),
        real_t *_vars,
        real_t _timestep,
        const char *filename
    );
};

// improved euler method (second order)
class EulerImproved : protected Solver {
  private:
    real_t *trials;
    void advance_internal(void);

  public:
    EulerImproved(
        int _dimension,
        real_t (*_system)(real_t*),
        real_t *init_vars,
        real_t _timestep,
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
