/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "neuron_layer.h"

#include <stdlib.h>

neuron_layer_t *neuron_layer_new(size_t neurons_size)
{
    neuron_layer_t *neuron_layer = malloc(sizeof(neuron_layer_t));

    neuron_layer->neurons = malloc(neurons_size * sizeof(neuron_t *));
    neuron_layer->neurons_size = neurons_size;

    return neuron_layer;
}

void neuron_layer_delete(neuron_layer_t *neuron_layer)
{
    free(neuron_layer->neurons);
    free(neuron_layer);
}

void neuron_layer_init(size_t weights_size, neuron_layer_t *neuron_layer)
{
    for (size_t i = 0; i < neuron_layer->neurons_size; i++) {
        neuron_t *neuron = neuron_new(weights_size);

        // Here should be provided other information, like the range of the rand
        // or the activation function
        neuron_init(neuron);

        neuron_layer->neurons[i] = neuron;
    }
}
