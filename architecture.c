#include "architecture.h"

int init_neuron(neuron neur, uint16_t input_size, int initialization, float init_param)
{
    neur.weights = (float *)malloc(input_size * sizeof(float));
    if (neur.weights == NULL)
    {
        fprintf("[ERROR] init_neuron(): Could not allocate %llu weights\n", input_size);
        return EXIT_FAILURE;
    }
    neur.biases = (float *)malloc(input_size * sizeof(float));
    if (neur.biases == NULL)
    {
        fprintf("[ERROR] init_neuron(): Could not allocate %llu weights\n", input_size);
        free(neur.weights);
        return EXIT_FAILURE;
    }

    for (uint16_t i = 0; i < input_size; i++)
    {

        switch (initialization)
        {
        case GLOROT_UNIFORM_INIT:
        case UNIFORM_INIT:
            neur.weights[i] = uniform_rand(-init_param, init_param);
            neur.biases[i] = uniform_rand(-init_param, init_param);
            break;
        case GLOROT_GAUSSIAN_INIT:
        case GAUSSIAN_INIT:
        default:
            neur.weights[i] = gauss_rand(0.0, init_param);
            neur.biases[i] = gauss_rand(0.0, init_param);
            break;
        }
    }

    return EXIT_SUCCESS;
}

int init_layer(layer *l, uint16_t input_size, uint16_t n_neurons, int initialization, int activation)
{
    l->input_size = input_size;
    l->n_neurons = n_neurons;
    l->initialization = initialization;
    l->activation = activation;

    l->output = (float *)malloc(n_neurons * sizeof(float));
    if (l->output == NULL)
    {
        fprintf("[ERROR] init_layer(): Could not allocate output (%llu floats)\n", n_neurons);
        free(l->ns);
        return EXIT_FAILURE;
    }
    memset(l->output, 0, n_neurons * sizeof(float));

    l->ns = (neuron *)malloc(n_neurons * sizeof(neuron));
    if (l->ns == NULL)
    {
        fprintf("[ERROR] init_layer(): Could not allocate %llu neurons in layer.\n", n_neurons);
        return EXIT_FAILURE;
    }

    float init_param = 0.0;
    switch (initialization)
    {
    case GLOROT_UNIFORM_INIT:
        init_param = sqrt(6.0 / ((float)input_size + (float)n_neurons));
        break;
    case GLOROT_GAUSSIAN_INIT:
        init_param = sqrt(6.0 / ((float)input_size + (float)n_neurons));
        break;
    case UNIFORM_INIT:
        init_param = 0.01;
        break;
    case GAUSSIAN_INIT:
    default:
        init_param = 0.1;
        break;
    }
    int ret = EXIT_SUCCESS;
    for (uint16_t i = 0; i < n_neurons; i++)
    {
        ret = init_neuron(l->ns[i], input_size, init_param, initialization);
        if (ret == EXIT_FAILURE)
        {
            fprintf(stderr, "[ERROR] init_layer(): Could not initiate neuron %llu\n", i);
            for (uint16_t j = 0; j < i; j++)
                free_neuron(l->ns[j]);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int addinit_layer(network *nk, uint16_t input_size, uint16_t n_neurons, int initialization, int activation)
{
    if (nk->current_layer_ind >= nk->n_layers - 1)
    {
        fprintf(stderr, "[ERROR] addinit_layer(): Network contains already %llu out of max. %llu layers, cannot add a new layer.\n",
                nk->current_layer_ind + 1, nk->n_layers);
        return EXIT_FAILURE;
    }
    layer *l = (layer *)malloc(sizeof(layer));
    if (l == NULL)
    {
        perror("[ERROR] add_layer(): Could not allocate new layer.");
        return EXIT_FAILURE;
    }
    if (nk->current_layer_ind > 0) // if layer is not the first, input_size ignored and forced to output size of previous layer
        input_size = nk->ls[nk->current_layer_ind - 1]->n_neurons;
    int ret = init_layer(l, input_size, n_neurons, initialization, activation);
    if (ret == EXIT_FAILURE)
    {
        perror("[ERROR] add_layer(): Could not initialize layer.");
        return EXIT_FAILURE;
    }
    nk->ls[nk->current_layer_ind] = l;
    nk->current_layer_ind = nk->current_layer_ind + 1;
    return EXIT_SUCCESS;
}

int add_layer(network *nk, layer *l)
{
    if (nk->current_layer_ind >= nk->n_layers - 1)
    {
        fprintf(stderr, "[ERROR] addinit_layer(): Network contains already %llu out of max. %llu layers, cannot add a new layer.\n",
                nk->current_layer_ind + 1, nk->n_layers);
        return EXIT_FAILURE;
    }
    nk->ls[nk->current_layer_ind] = l;
    nk->current_layer_ind = nk->current_layer_ind + 1;
    return EXIT_SUCCESS;
}

void free_neuron(neuron neur)
{
    free(neur.weights);
    free(neur.biases);
    return;
}

void free_layer(layer *l)
{
    for (uint16_t i = 0; i < l->n_neurons; i++)
        free_neuron(l->ns[i]);
    free(l->ns);
    return;
}

void free_network(network *nk)
{
    for (uint16_t i = 0; i < nk->current_layer_ind; i++)
        free_layer(nk->ls[i]);
    free(nk->ls);
    return;
}
