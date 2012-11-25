#include "base.h"

double rand_double(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

real_t signum(real_t n) {
    real_t c = (n < 0) ? -1.0 : 1.0;
    return c;
}

