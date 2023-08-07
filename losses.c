#include "losses.h"

// Loss functions for regression tasks

float mse(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s])
{
    float sum = 0.0;
    for (uint16_t i = 0; i < batch_s; i++)
        sum += (y_true[i] - y_pred[i]) * (y_true[i] - y_pred[i]);
    sum /= (float)batch_s;
    return sum;
}

float msle(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s])
{
    float sum = 0.0;
    for (uint16_t i = 0; i < batch_s; i++)
        sum += (log(1 + y_pred[i]) - (float)log(1.0 + (double)y_true[i])) * (log(1 + y_pred[i]) - (float)log(1.0 + (double)y_true[i]));
    sum /= (float)batch_s;
    return sum;
}

float mae(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s])
{
    float sum = 0.0, toadd = 0.0;
    for (uint16_t i = 0; i < batch_s; i++)
    {
        toadd = (y_true[i] > y_pred[i]) ? (y_true[i] - y_pred[i]) : (y_pred[i] - y_true[i]);
        sum += toadd;
    }
    sum /= (float)batch_s;
    return sum;
}

// Loss functions for binary classification tasks

float binary_cross_entropy(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s])
{
    // y_true = 0 or 1
    float sum = 0.0;
    for (uint16_t i = 0; i < batch_s; i++)
        sum -= (y_true[i] * (float)log((double)y_pred[i]) + (1 - y_true[i]) * (float)log(1.0 - (double)y_pred[i]));
    sum /= (float)batch_s;
    return sum;
}

float hinge(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s])
{
    // y_true = -1 or 1
    float sum = 0.0, toadd = 0.0;
    for (uint16_t i = 0; i < batch_s; i++)
    {
        toadd = (y_true[i] * y_pred[i] > 1) ? 1 - (y_true[i] * y_pred[i]) : 0.0;
        sum += toadd;
    }
    sum /= (float)batch_s;
    return sum;
}

float sq_hinge(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s])
{
    // y_true = -1 or 1
    float sum = 0.0, toadd = 0.0;
    for (uint16_t i = 0; i < batch_s; i++)
    {
        toadd = (y_true[i] * y_pred[i] > 1) ? 1 - (y_true[i] * y_pred[i]) : 0.0;
        toadd *= toadd;
        sum += toadd;
    }
    sum /= (float)batch_s;
    return sum;
}

// TODO: loss functions for multiclass classification (and make biases stable to 1)

float multiple_cross_entropy(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s])
{
    float sum = 0.0;
    for (uint16_t i = 0; i < batch_s; i++)
        sum -= y_true[i] * (float)log((double)y_pred[i]);
    sum /= (float)batch_s;
    return sum;
}

float kullback_leibler(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s])
{
    float sum = 0.0;
    for (uint16_t i = 0; i < batch_s; i++)
        sum += y_true[i] * log((float)(y_true[i] / y_pred[i]));
    sum /= (float)batch_s;
    return sum;
}