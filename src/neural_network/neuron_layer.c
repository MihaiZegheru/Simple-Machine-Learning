/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "neuron_layer.h"

neuron_layer_t *neuron_layer_new(size_t neurons_size)
{
    neuron_layer_t *neuron_layer = malloc(sizeof(neuron_layer_t));
    if (!neuron_layer) {
        exit(-1);
    }

    neuron_layer->neurons_size = neurons_size;
    neuron_layer->neurons = malloc(neurons_size * sizeof(neuron_t *));
    if (!neuron_layer->neurons) {
        exit(-1);
    }
    
    return neuron_layer;
}

void neuron_layer_delete(neuron_layer_t *neuron_layer)
{
    for (size_t i = 0; i < neuron_layer->neurons_size; i++) {
        neuron_delete(neuron_layer->neurons[i]);
    }
    free(neuron_layer->neurons);
    free(neuron_layer);
}

void neuron_layer_init(size_t weights_size, neuron_layer_t *neuron_layer)
{
    for (size_t i = 0; i < neuron_layer->neurons_size; i++) {
        neuron_t *neuron = neuron_new(weights_size);
        neuron_init(neuron);

        neuron_layer->neurons[i] = neuron;
    }
}
