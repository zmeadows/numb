#include "stdio.h"
#include "nbody.h"
#include "solver.h"

#define X 0
#define Y 1
#define Z 2

const real_t sigma = 10.0;
const real_t rho = 28.0;
const real_t beta = 8.0/3.0;

real_t x_dot(real_t *vars) { return sigma*(vars[Y] - vars[X]); }
real_t y_dot(real_t *vars) { return vars[X]*(rho - vars[Z]) - vars[Y]; }
real_t z_dot(real_t *vars) { return vars[X]*vars[Y] - beta*vars[Z]; }

int main(void) {
    //real_t masses[5] = { 1, 1, 1, 1, 1000};
    //real_t poss[10] = {1,  0, 0, 1, -1, 0,  0, -1, 0, 0};
    //real_t vels[10] = {0, -0.5, 0.5, 0,  0, 0.5, -0.5,  0, 0, 0};
    nbody_solver test(2,10,1e-4);
    /*
    reals_f lorenz_equations[] = { &x_dot, &y_dot, &z_dot };
    double inits[3] = {1.0, 1.0, 1.0};
    RungeKutta4 system(3,lorenz_equations,inits,0.001);

    while (system.steps() <= 40000) {
        system.advance_step();
        system.print_stats();
    }
    */

    
    
    return 0;
}
