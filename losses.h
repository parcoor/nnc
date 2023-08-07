#ifndef LOSSES_H
#define LOSSES_H

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

float mse(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s]);
float msle(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s]);
float mae(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s]);
float binary_cross_entropy(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s]);
float hinge(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s]);
float sq_hinge(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s]);
float multiple_cross_entropy(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s]);
float kullback_leibler(uint16_t batch_s, float y_pred[batch_s], float y_true[batch_s]);

#endif