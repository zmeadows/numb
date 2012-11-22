#include "stdio.h"
#include "math.h"
#include "root.h"
#include "matrix.h"
#include "nbody.h"

#define X 0
#define Y 1
#define Z 2

double sigma = 10.0;
double rho = 28.0;
double beta = 8.0/3.0;

double x_dot(double *vars) { return sigma*(vars[Y] - vars[X]); }
double y_dot(double *vars) { return vars[X]*(rho - vars[Z]) - vars[Y]; }
double z_dot(double *vars) { return vars[X]*vars[Y] - beta*vars[Z]; }

double f(double x) { return x*x*x - 6*x*x + 7*x + 11; }

int main(void) {
  /*
    func<double> lorenz_equations[] = { &x_dot, &y_dot, &z_dot };
    double inits[3] = {1.0, 1.0, 1.0};
    const char *name = "logfile";
    RungeKutta4<double> system(3,lorenz_equations,inits,0.001,name);
    system.solve(50.0);
  */
    return 0;
}
