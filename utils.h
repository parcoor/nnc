#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <math.h>

#define NAME_SIZE 20

float gauss_rand(float mean, float sigma);
float uniform_rand(float min_v, float max_v);
void print_array(FILE *f, size_t n, float arr[n]);
void print_neuron(FILE *f, neuron neur);
void get_activation_name(char activation_name[NAME_SIZE], int activation);
void print_layer(FILE *f, layer l);
void print_network(FILE *f, network nk);

#endif