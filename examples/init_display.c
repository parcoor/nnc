#include "../architecture.h"
#include "../activations.h"
#include "../nnc_utils.h"


int example_init_display()
{
    srand(time(NULL));  // Init randomness
    int ret;
    network nk;
    uint16_t n_layers = 3;

    printf("[INFO] Initializing and displaying a network with 3 layers:\n");

    init_network(&nk,  n_layers);
    // First layer with input of size 5, 7 neurons, Glorot Gaussian weights & biases initialization and ReLu activation:
    addinit_layer(&nk, 5, 7, GLOROT_UNIFORM_INIT, RELU_ACT);
    // Input size is unrelevant for the following layers, will be set to output size of previous layer anyway
    addinit_layer(&nk, 0, 3, GLOROT_UNIFORM_INIT, RELU_ACT);
    addinit_layer(&nk, 0, 1, GLOROT_GAUSSIAN_INIT, SIGMOID_ACT);

    print_network(stdout,&nk);
    free_network(&nk);

    return EXIT_SUCCESS;
}

 int main()
 {
    int ret;
    ret = example_init_display();
    return ret;
 }