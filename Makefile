CC = gcc
CFAGS = -Wall -Werror
# LFLAGS = -lm  # For Linux


example_init_display.exe: examples/init_display.c architecture.c activations.c persistence.c nnc_utils.c
	$(CC) -o $@ $^ $(CFLAGS) -lm

example_init_display_debug.exe: examples/init_display.c architecture.c activations.c persistence.c nnc_utils.c
	$(CC) -o $@ $^ $(CFLAGS) -lm -g -O0