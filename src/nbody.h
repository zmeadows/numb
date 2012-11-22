#ifndef NBODY_H
#define NBODY_H

#include "base.h"
#include "stddef.h"

class nbody_solver {
private:
    const size_t NDIM;
    const size_t NBODIES;

    real_t step_size;
    real_t time_elapsed;
    size_t steps_taken;
    real_t potential_energy;
    void predict_step(void);
    void evolve_step(void);
    void correct_step(void);
public:
    void evolve(void);
};

#endif
