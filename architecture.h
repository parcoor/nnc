#ifndef ARCHITECTURE_H
#define ARCHITECTURE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define GLOROT_UNIFORM_INIT 0
#define GLOROT_GAUSSIAN_INIT 1
#define UNIFORM_INIT 2
#define GAUSSIAN_INIT 3
#define HE_INIT 4


typedef struct neuron {
    uint16_t n;
    double weights[n];
    double biases[n];
} neuron;

typedef struct layer {
    uint16_t n_neurons;
    neuron ns[n_neurons];
    int activation;
    int initialization;
} layer;

typedef struct network {
    uint16_t n_layers;
    layer ls[n_layers];
} network;


#endif