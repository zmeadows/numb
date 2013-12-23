#include "root.h"

RootFinder::RootFinder(real_f eqn, double tol, int max_iter)
    : current_iteration(0),
      max_iterations(max_iter),
      tolerance(tol),
      equation(eqn),
      root(0)
{
};

std::pair<bool,double>
RootFinder::find_root(void)
{
    std::pair <bool,double> result;
    while (current_iteration < max_iterations) {
        if (iterate()) return (std::make_pair(true,root));
        ++current_iteration;
    }
    return (std::make_pair(false,root));
};

Bisection::Bisection(real_f eqn, double x_min, double x_max, double tol, int max_iter)
    : RootFinder(eqn, tol, max_iter),
      a(x_min),
      b(x_max)
{
};

bool
Bisection::iterate(void)
{
    root = (a + b)/2;
    if (equation(root) == 0 || (b - a)/2 < tolerance) return true;
    (equation(a)*equation(root)<0) ? b = root : a = root;
    return false;
};

// Newton::Newton(real_f _equation, real_f _derivative, double guess, double _tolerance, int _max_iterations)
//     : RootFinder(_equation, _tolerance, _max_iterations),
//       derivative(_derivative),
//       prev(guess)
// {
// };
//
// bool
// Newton::iterate(void)
// {
//     return false;
// };

