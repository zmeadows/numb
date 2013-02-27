#ifndef ROOT_H
#define ROOT_H

#include "base.h"
#include "stdio.h"
#include <utility>
/*
// base root-finding class that each type of root-finder inherits from
class Finder {
  protected:
    int current_iteration;
    int max_iterations;
    double tolerance;
    realfunc equation;
    double root;
    bool debug;
    bool log_output;
    virtual bool iterate(void) = 0;
  public:
    std::pair <bool,double> find_root(void);
    Finder(realfunc eqn, double tol, int max_iter);
};

// classic bisection method
class Bisection : public Finder {
  private:
    double a;
    double b;
    bool iterate(void);
  public:
    Bisection(realfunc eqn, double x_min, double x_max,  double tol, int max_iter);
};

// newton's method
class Newton : public Finder {
  private:
    bool iterate(void);
    realfunc derivative;
    double prev;
  public:
    Newton(realfunc _equation, realfunc _derivative, double guess, double _tolerance, int _max_iterations);
};
*/
#endif
