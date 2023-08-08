CC = gcc
CFLAGS = -Wall -Werror
DFLAGS = -g -O0
DEPS = architecture.c activations.c nnc_utils.c pass.c losses.c metrics.c
# LFLAGS = -lm  # For Linux


init_store_load.exe: examples/init_store_load.c $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) -lm

xor_training_cyclical.exe: examples/xor_training_cyclical.c $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) -lm

sin_history.exe: examples/sin_history.c $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) -lm
