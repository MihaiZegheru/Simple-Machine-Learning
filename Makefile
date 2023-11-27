#
#   Copyright (c) 2023 Mihai Zegheru
#   All rights reserved.
#

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SOURCES=main.c\
		train_field.c\
		train_set.c\
		io_utils.c\
		neuron.c\
		random_utils.c\
		neuron_layer.c\
		neural_network.c

build:
	$(CC) $(CFLAGS) $(SOURCES) -o SimpleMachineLearning.exe -lm
