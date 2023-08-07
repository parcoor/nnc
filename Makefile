CC = gcc
CFLAGS = -Wall -Werror
DFLAGS = -g -O0
# LFLAGS = -lm  # For Linux


example_init_display.exe: examples/init_display.c architecture.c activations.c persistence.c nnc_utils.c pass.c
	$(CC) -o $@ $^ $(CFLAGS) -lm

example_init_display_debug.exe: examples/init_display.c architecture.c activations.c persistence.c nnc_utils.c pass.c
	$(CC) -o $@ $^ $(CFLAGS) -lm $(DFLAGS)

xor_training.exe: examples/xor_training.c architecture.c activations.c nnc_utils.c pass.c losses.c metrics.c
	$(CC) -o $@ $^ $(CFLAGS) -lm

xor_training_debug.exe: examples/xor_training.c architecture.c activations.c nnc_utils.c pass.c losses.c metrics.c
	$(CC) -o $@ $^ $(CFLAGS) -lm $(DFLAGS)