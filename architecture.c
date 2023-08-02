#include "architecture.h"


int init_layer(uint16_t input_size, layer* l)
{
    double initialization_param = 0.0;
    switch(l->initialization) {
        case GLOROT_UNIFORM_INIT:
            param = sqrt(6.0 / ((double)input_size + (double)l->n_neurons));
            break;
        case GLOROT_GAUSSIAN_INIT:
            param = sqrt(6.0 / ((double)input_size + (double)l->n_neurons));
            break;
        case UNIFORM_INIT:
            param = 0.01;
            break;
        case GAUSSIAN_INIT:
        default:
            param = 0.1;
            break;
    }

    for (uint16_t i = 0; i < l->n_neurons; i++)
    {
        l->ns->n = input_size;

        switch(l->initialization) {
            case GLOROT_UNIFORM_INIT:
            case UNIFORM_INIT:
                l->ns->weights[i] = uniform_rand(-param, param);
                l->ns->biases[i] = uniform_rand(-param, param);
                break;
            case GLOROT_UNIFORM_INIT:
            case GAUSSIAN_INIT:
            default:
                l->ns->weights[i] = gauss_rand(0.0, param);
                l->ns->biases[i] = gauss_rand(0.0, param);
                break;
        }
    }
}