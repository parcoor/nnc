#include "../src/architecture.h"
#include "../src/activations.h"
#include "../src/nnc_utils.h"
#include "../src/pass.h"
#include "../src/losses.h"
#include "../src/metrics.h"

#define PI 3.141592

void generate_sin_batch(uint16_t batch_s, float X[batch_s][3], float y[batch_s][1])
{
    for (uint16_t i = 0; i < batch_s; i++)
    {
        X[i][0] = uniform_rand(-1.0 / 3.0, 1.0 / 3.0);
        X[i][1] = uniform_rand(-1.0 / 3.0, 1.0 / 3.0);
        X[i][2] = uniform_rand(-1.0 / 3.0, 1.0 / 3.0);
        y[i][0] = (float)sin((double)(X[i][0] + X[i][1] + X[i][2]));
    }
}

int main()
{
    srand(time(NULL)); // Init randomness
    network nk;
    uint16_t n_layers = 4;

    printf("[INFO] Initializing and displaying a network with 3 layers:\n");

    init_network(&nk, n_layers);
    addinit_layer(&nk, 3, 1, GLOROT_UNIFORM_INIT, TANH_ACT);
    addinit_layer(&nk, 0, 3, GLOROT_UNIFORM_INIT, TANH_ACT);
    addinit_layer(&nk, 0, 3, GLOROT_UNIFORM_INIT, TANH_ACT);
    addinit_layer(&nk, 0, 1, GLOROT_UNIFORM_INIT, TANH_ACT);

    uint16_t batch_s = 16, input_s = 3, output_s = 1;
    float X[batch_s][input_s];
    float y_true[batch_s][output_s];
    float y_pred[batch_s][output_s];
    float error[batch_s][output_s];
    float loss[batch_s][output_s];
    float avg_error = 0.0, avg_mse_loss = 0.0, avg_mae_loss = 0.0;
    float lr = 0.001;

    FILE *history_f = fopen("examples/sin_training.csv", "w");
    fprintf(history_f, "batch_ind,error,mse,mae\n");

    uint16_t n_batches = 1000;
    for (uint16_t batch_ind = 0; batch_ind < n_batches; batch_ind++)
    {
        // Generate training data
        generate_sin_batch(batch_s, X, y_true);

        // Forward training data through the neural network nk
        batch_forward(&nk, batch_s, input_s, X, output_s, y_pred);
        // Compute error for back-propagation: parameter derivative = true
        loss_batch(MSE_LOSS, batch_s, output_s, y_pred, y_true, true, error);
        avg_error = avg_matrix((size_t)batch_s, (size_t)output_s, error);
        // compute loss for metric: derivative = false
        loss_batch(MSE_LOSS, batch_s, output_s, y_pred, y_true, false, loss);
        avg_mse_loss = avg_matrix((size_t)batch_s, (size_t)output_s, loss);
        loss_batch(MAE_LOSS, batch_s, output_s, y_pred, y_true, false, loss);
        avg_mae_loss = avg_matrix((size_t)batch_s, (size_t)output_s, loss);
        // Print out current info about loss and accuracy
        printf("[INFO] Sin Training: batch %u: MSE error = %f, MSE loss = %f, MAE loss = %f\n", batch_ind, avg_error, avg_mse_loss, avg_mae_loss);
        fprintf(history_f, "%u,%f,%f,%f\n", batch_ind, avg_error, avg_mse_loss, avg_mae_loss);
        // backpropagation for training (weight adaptation)
        backpropagation_batch(&nk, batch_s, output_s, error, input_s, X, lr);
    }

    print_matrix(stdout, batch_s, output_s, y_true);
    print_matrix(stdout, batch_s, output_s, y_pred);

    free_network(&nk);
    fclose(history_f);
    return EXIT_SUCCESS;
}