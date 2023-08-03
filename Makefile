CC = gcc
CFAGS = -Wall -Werror
# LFLAGS = -lm  # For Linux


example_init_display: examples/init_display.c architecture.c activations.c nnc_utils.c
	$(CC) -o $@ $^ $(CFLAGS)