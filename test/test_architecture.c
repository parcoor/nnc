#include "../architecture.h"
#include "../activations.h"
#include "../utils.h"


int test_init_layer()
{
    layer l = {
        .n_neurons = 6,
        .ns = {0},
        .activation = RELU_ACT,
        .initialization = GLOROT_GAUSSIAN_INIT,
    }

    uint16_t input_size = 3;
    init_layer(input_size, &l);



    return EXIT_SUCCESS;
}