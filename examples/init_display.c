#include "../architecture.h"
#include "../activations.h"
#include "../persistence.h"
#include "../nnc_utils.h"
#include "../pass.h"

int example_init_display()
{
    srand(time(NULL)); // Init randomness
    int ret;
    network nk;
    uint16_t n_layers = 3;

    printf("[INFO] Initializing and displaying a network with 3 layers:\n");

    init_network(&nk, n_layers);
    // First layer with input of size 5, 7 neurons, Glorot Gaussian weights & biases initialization and ReLu activation:
    addinit_layer(&nk, 5, 7, GLOROT_UNIFORM_INIT, RELU_ACT);
    // Input size is unrelevant for the following layers, will be set to output size of previous layer anyway
    addinit_layer(&nk, 0, 3, GLOROT_UNIFORM_INIT, RELU_ACT);
    addinit_layer(&nk, 0, 1, GLOROT_GAUSSIAN_INIT, SIGMOID_ACT);

    print_network(stdout, &nk);
    // Persist network
    char *network_fp = "examples/network.txt";
    printf("[INFO] Persisting network at %s\n", network_fp);
    persist_network(&nk, network_fp);
    // Load network
    printf("[INFO] Loading network at %s\n", network_fp);
    network loaded_nk;
    load_network(&loaded_nk, network_fp);
    printf("[INFO] network loaded:\n");
    print_network(stdout, &loaded_nk);

    // Forward pass
    uint16_t batch_s = 3;
    uint16_t input_s = 5;
    float batch[batch_s][input_s];
    for (uint16_t i = 0; i < batch_s; i++)
        for (uint16_t j = 0; j < input_s; j++)
            batch[i][j] = -0.4 + 0.2 * (float)i + (float)j / (float)input_s;
    uint16_t output_s = 1;
    float output[batch_s][output_s];
    batch_forward(&loaded_nk, batch_s, input_s, batch, output_s, output);
    printf("Batch (before forward):\n");
    print_matrix(stdout, (size_t)batch_s, (size_t)input_s, batch);
    printf("Output (after forward):\n");
    print_matrix(stdout, (size_t)batch_s, (size_t)output_s, output);

    free_network(&nk);
    free_network(&loaded_nk);

    return EXIT_SUCCESS;
}

int main()
{
    int ret;
    ret = example_init_display();
    return ret;
}