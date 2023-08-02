#include "activations.h"


double identity(double x, bool derivative)
{
    double ret = derivative ? 1 : x;
    return ret;
}

double logistic(double x, bool derivative)
{
    double ret = 1 / (1 + exp(-x));
    if (derivative)
        ret *= (1 - ret);
    return ret;
}

double relu(double x, bool derivative)
{
    double ret = 0.0;
    if (x > 0) 
        ret = derivative ? 1.0 : x;
    return ret;
}

double tanh(double x, bool derivative)
{
    double ret = (exp(x) - exp(-x)) / (exp(x) + exp(-x));
    if (derivative)
        ret = 1 - ret * ret;
    return ret;
}