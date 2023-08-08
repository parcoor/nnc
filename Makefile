CC = gcc
CFLAGS = -Wall -Werror
DFLAGS = -g -O0
DEPS = src/architecture.c src/activations.c src/nnc_utils.c src/pass.c src/losses.c src/metrics.c
# LFLAGS = -lm  # For Linux


init_store_load.exe: examples/init_store_load.c $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) -lm

xor_training_cyclical.exe: examples/xor_training_cyclical.c $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) -lm

sin_history.exe: examples/sin_history.c $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) -lm
