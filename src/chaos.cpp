#include "chaos.h"
#include "stdio.h"

LogisticMap::LogisticMap(int _resolution)
    : resolution(_resolution)
{
};

void
LogisticMap::print_bifurcation_diagram(void)
{
    double u,x_0,x;
    for (u = 1.0; u <= 4.0; u += 3.0 / resolution)
    {
        for (x_0 = 0.1; x_0 <= 0.9; x_0 += 0.05)
        {
            x = x_0;

            int i;
            for (i=1; i<500; ++i)
            {
                x = u * x * (1 - x);
            }

            for (i=500; i<1000; ++i)
            {
                x = u * x * (1 - x);
                printf("%.4g\t %.4g\t\n", u, x);
            }

        }
    }
};
