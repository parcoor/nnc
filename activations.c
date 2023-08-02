#include "activations.h"

float identity(float x, bool derivative)
{
    float ret = derivative ? 1 : x;
    return ret;
}

float logistic(float x, bool derivative)
{
    float ret = 1 / (1 + exp(-(double)x));
    if (derivative)
        ret *= (1 - ret);
    return ret;
}

float relu(float x, bool derivative)
{
    float ret = 0.0;
    if (x > 0)
        ret = derivative ? 1.0 : x;
    return ret;
}

float tanh(float x, bool derivative)
{
    double xd = (double)x;
    float ret = (exp(xd) - exp(-xd)) / (exp(xd) + exp(-xd));
    if (derivative)
        ret = 1 - ret * ret;
    return ret;
}