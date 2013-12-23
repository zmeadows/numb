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
    real_f equation;
    double root;
    virtual bool iterate(void) = 0;
  public:
    std::pair<bool,double> find_root(void);
    RootFinder(real_f eqn, double tol, int max_iter);
};

// classic bisection method
class Bisection : public RootFinder {
  private:
    double a;
    double b;
    bool iterate(void);
  public:
    Bisection(real_f eqn, double x_min, double x_max,  double tol, int max_iter);
};

// newton's method
// class Newton : public RootFinder {
//   private:
//     bool iterate(void);
//     // real_f derivative;
//     // double prev;
//   public:
//     Newton(real_f _equation, real_f _derivative, double guess, double _tolerance, int _max_iterations);
// };

#endif
