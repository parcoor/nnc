#include "../architecture.h"
#include "../activations.h"
#include "../nnc_utils.h"
#include "../pass.h"
#include "../losses.h"
#include "../metrics.h"

void generate_xor_batch(uint16_t batch_s, float X[batch_s][2], float y[batch_s][1])
{
    for (uint16_t i = 0; i < batch_s; i++)
    {
        X[i][0] = uniform_rand(0.0, 1.0);
        X[i][1] = uniform_rand(0.0, 1.0);
        y[i][0] = (float)((X[i][0] > 0.5) != (X[i][1] > 0.5));
    }
}

int main()
{
    srand(time(NULL)); // Init randomness
    network nk;
    uint16_t n_layers = 3;

    printf("[INFO] Initializing and displaying a network with 3 layers:\n");

    init_network(&nk, n_layers);
    addinit_layer(&nk, 2, 1, GLOROT_UNIFORM_INIT, SIGMOID_ACT);
    addinit_layer(&nk, 0, 1, GLOROT_UNIFORM_INIT, RELU_ACT);
    addinit_layer(&nk, 0, 1, GLOROT_UNIFORM_INIT, SIGMOID_ACT);

    uint16_t batch_s = 16, input_s = 2, output_s = 1;
    float X[batch_s][input_s];
    float y_true[batch_s][output_s];
    float y_pred[batch_s][output_s];
    float error[batch_s][output_s];
    float loss[batch_s][output_s];
    float avg_loss = 0.0;
    float lr = 0.0;
    float accuracy = 0.0;

    uint16_t n_batches = 1000;
    for (uint16_t batch_ind = 0; batch_ind < n_batches; batch_ind++)
    {
        // Generate training data
        generate_xor_batch(batch_s, X, y_true);

        // Compute cyclical learning rate
        lr = sin((double)batch_ind / 10) * 0.001 + 0.002;

        // Forward training data through the neural network nk
        batch_forward(&nk, batch_s, input_s, X, output_s, y_pred);
        // Compute accuracy metric
        accuracy = acc(batch_s, y_true, y_pred, 0.5);
        // Compute error for back-propagation: parameter derivative = true
        loss_batch(BINARY_CROSS_ENTROPY_LOSS, batch_s, output_s, y_pred, y_true, true, error);
        // compute loss for metric: derivative = false
        loss_batch(BINARY_CROSS_ENTROPY_LOSS, batch_s, output_s, y_pred, y_true, false, loss);
        avg_loss = avg_matrix((size_t)batch_s, (size_t)output_s, loss);
        // Print out current info about loss and accuracy
        printf("[INFO] XOR Training: Loss at batch %u = %f, acc=%f\n", batch_ind, avg_loss, accuracy);
        // backpropagation for training (weight adaptation)
        backpropagation_batch(&nk, batch_s, output_s, error, input_s, X, lr);
    }

    free_network(&nk);
    return EXIT_SUCCESS;
}