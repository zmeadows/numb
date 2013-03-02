#ifndef ROOT_H
#define ROOT_H

#include "base.h"
#include "stdio.h"
#include <utility>

/* base root-finding class */
class RootFinder {
  protected:
    int current_iteration;
    int max_iterations;
    double tolerance;
    func_R_R equation;
    double root;
    virtual bool iterate(void) = 0;
  public:
    std::pair<bool,double> find_root(void);
    RootFinder(func_R_R eqn, double tol, int max_iter);
};

// classic bisection method
class Bisection : public RootFinder {
  private:
    double a;
    double b;
    bool iterate(void);
  public:
    Bisection(func_R_R eqn, double x_min, double x_max,  double tol, int max_iter);
};

// newton's method
class Newton : public RootFinder {
  private:
    bool iterate(void);
    func_R_R derivative;
    double prev;
  public:
    Newton(func_R_R _equation, func_R_R _derivative, double guess, double _tolerance, int _max_iterations);
};

#endif
