# NNC Neural Network in C - By Parcoor

This library allows to build, train, store and use neural networks.

It is written entirely in C, with no external dependencies to e.g. linear algebra libraries. Thus it can run out-of-the-box on (almost) any device. It also easily allows a very fine level of inner control and observability.

## Examples

The folder [examples](examples/) shows different ways to use this library:

- [init_store_load](examples/init_store_load.c) shows how to initialize a neural network, persist it and re-load it from the disk. Compile with `make init_store_load`
- [sin_history](examples/sin_history.c) shows how to use NNC for a regression task (approximating a _sinus_ function) and store the training history in a csv file. Compile with `make sin_history`
- [xor_training_cyclical](examples/xor_training_cyclical.c) shows how to use NNC for a classification task, with [cyclical learning rates](https://mancap314.github.io/cyclical-learning-rates-with-tensorflow-implementation.html). Compile with `make xor_training_cyclical`

## Structure

- [architecture.h](architecture.h) contains the definition of the different bricks to build a neural network, such as the neural network itself, a layer, a neuron.
- [activation.h](activations.h) contains the definition of the different activation functions that can be used for the layers.
- [losses.h](losses.h) contains the definition of the loss function that can be used to train a neural netwwork through backpropagation, depending on the task at hand (regression, classification...)
- [metrics.h](metrics.h) contains metrics that can be used to assess a neural network training or inference.
