#include "utils.h"
#include "architecture.h"
#include "activations.h"

// Knuth & Marsaglia: https://c-faq.com/lib/gaussian.html
float gauss_rand(float mean, float sigma)
{
	static float V1, V2, S;
	static int phase = 0;
	float X;

	if (phase == 0)
	{
		do
		{
			float U1 = (float)rand() / RAND_MAX;
			float U2 = (float)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return sigma * (X + mean);
}

float uniform_rand(float min_v, float max_v)
{
	float value = (float)rand() / (float)RAND_MAX;
	return value * (max_v - min_v) + min_v;
}

// Functions for printing neuron, layer, network

void print_array(FILE *f, size_t n, float arr[n])
{
	printf("[");
	for (size_t i = 0; i < n; i++)
	{
		fprintf(f, "%f%s", arr[i], (i == n - 1) ? ", " : "]\n");
	}
	return;
}

void print_neuron(FILE *f, neuron neur)
{
	printf("Input size: %llu\n", neur.input_size);
	printf("weights: ");
	print_array(f, (size_t)neur.input_size, neur.weights);
	printf("\nbiases: ");
	print_array(f, (size_t)neur.input_size, neur.biases);
}

void get_activation_name(char activation_name[NAME_SIZE], int activation)
{
	switch (activation)
	{
	case IDENTITY_ACT:
		strncpy(activation_name, "Identity", 9);
		break;
	case LOGISTIC_ACT:
		strncpy(activation_name, "Logistic", 9);
		break;
	case RELU_ACT:
		strncpy(activation_name, "ReLu", 5);
		break;
	case TANH_ACT:
		strncpy(activation_name, "Tanh", 5);
		break;
	default:
		strncpy(activation_name, "Unknown", 8);
		break;
	}
}

void print_layer(FILE *f, layer l)
{
	char activation_name[NAME_SIZE];
	get_activation_name(activation_name, l.activation);
	fprintf(f, "Input Size: %llu\nNumber of Neurons: %llu\nActivation: %s\n", l.input_size, l.n_neurons, activation_name);
	for (uint16_t i = 0; i < l.n_neurons; i++)
	{
		fprintf(f, "= Neuron %llu\n", i);
		print_neuron(f, l.ns[i]);
	}
}

void print_network(FILE *f, network nk)
{
	printf("=== Network\nMax Number of Layers: %llu\nCurrent Number of Layers: %llu\n", nk.n_layers, nk.current_layer_ind);
	for (uint16_t i = 0; i < nk.current_layer_ind; i++)
	{
		fprintf(f, "== Layer %llu\n", i);
		print_layer(f, nk.ls[i]);
	}
}

// TODO: Define functions for persisting / loadindg persisted network
