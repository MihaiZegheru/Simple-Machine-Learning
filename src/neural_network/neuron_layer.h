/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#ifndef NEURON_LAYER_H__
#define NEURON_LAYER_H__

#include <stdlib.h>

#include "neuron.h"

typedef struct {
    neuron_t **neurons;
    size_t neurons_size;
} neuron_layer_t;

/**
 * @brief Instantiate a new neuron lyaer and return it
 * 
 * @param neurons_size 
 * @return neuron_layer_t* 
 */
neuron_layer_t *neuron_layer_new(size_t neurons_size);

/**
 * @brief Delete a provided neuron layer
 * 
 * @param neuron_layer 
 */
void neuron_layer_delete(neuron_layer_t *neuron_layer);

/**
 * @brief Propagates through the neuron layer and initialises its values
 * 
 * @param weights_size 
 * @param neuron_layer 
 */
void neuron_layer_init(size_t weights_size, neuron_layer_t *neuron_layer);

#endif
