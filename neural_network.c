/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "neural_network.h"

neural_network_t *neural_network_new(size_t neuron_layers_size)
{
    neural_network_t *neural_network = malloc(sizeof(neural_network));

    neural_network->neuron_layers = malloc(neuron_layers_size *
                                           sizeof(neuron_layer_t));
    neural_network->neuron_layers_size = neuron_layers_size;

    return neural_network;
}

void neural_network_delete(neural_network_t *neural_network)
{
    free(neural_network->neuron_layers);
    free(neural_network);
}

void neural_network_init(size_t input_size, size_t *neurons_sizes,
                         neural_network_t *neural_network)
{
    if (sizeof(neurons_sizes) / sizeof(size_t) !=
        neural_network->neuron_layers_size) {
        // ERR: Number of neurons sizes not the same as neuron layers
        exit(-1);
    }

    for (size_t i = 0; i < neural_network->neuron_layers_size; i++) {
        neuron_layer_t *neuron_layer = neuron_layer_new(neurons_sizes[i]);

        size_t neurons_size = input_size;
        if (i) {
            neurons_size = neurons_sizes[i - 1];
        }
        
        neuron_layer_init(neurons_size, neuron_layer);

        neural_network->neuron_layers[i] = neuron_layer;
    }
}
