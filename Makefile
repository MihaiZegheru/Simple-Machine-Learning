#
#   Copyright (c) 2023 Mihai Zegheru
#   All rights reserved.
#

CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LIBS=-lm

EXE=SimpleMachineLearning.exe

SRC=src
OUT=out
RES=res

SOURCES=$(SRC)/main.c\
		$(SRC)/data_storing/train_field.c\
		$(SRC)/data_storing/train_set.c\
		$(SRC)/neural_network/neuron.c\
		$(SRC)/neural_network/neuron_layer.c\
		$(SRC)/neural_network/neural_network.c\
		$(SRC)/utils/io_utils.c\
		$(SRC)/utils/random_utils.c\
		$(SRC)/utils/math_utils.c

build:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUT)/$(EXE) $(LIBS)

clean:
	rm $(OUT)/$(EXE)
