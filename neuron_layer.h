/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#ifndef NEURON_LAYER_H__
#define NEURON_LAYER_H__

#include <stddef.h>

#include "neuron.h"

typedef struct {
    neuron_t **neurons;
    size_t neurons_size;
} neuron_layer_t;

neuron_layer_t *neuron_layer_new(size_t neurons_size);
void neuron_layer_delete(neuron_layer_t *neuron_layer);

void neuron_layer_init(size_t weights_size, neuron_layer_t *neuron_layer);

#endif