#include "utils.h"


// Knuth & Marsaglia: https://c-faq.com/lib/gaussian.html
double gauss_rand(double mean, double sigma)
{
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if(phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
			} while(S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	} else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return sigma * (X + mean);
}


double uniform_rand(double min_v, double max_v)
{
    double value = (double)rand() / (double)RAND_MAX;
    return value * (max_v - min_v) + min_v;
}

// TODO: Define functions for printing neuron, layer, network
void print_array(size_t n, double arr[n])
{
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%f%s", arr[i], (i == n - 1) ? ", ": "]\n");
    }
    return;
}

void print_neuron(neuron* neur)
{
    printf("weights: ");
    print_array((size_t)neur->n, neur->weights);
    printf("\nbiases: ");
    print_array((size_t)n, neur->biases);
}

// TODO: Define functions for persisting / loadind persisted network
