/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#ifndef NEURON_H__
#define NEURON_H__

#include <stdlib.h>

typedef struct {
    float *weights;
    size_t weights_size;

    float bias;
} neuron_t;

/**
 * @brief Instantiate a new neuron and return it
 * 
 * @param weights_size 
 * @return neuron_t* 
 */
neuron_t *neuron_new(size_t weights_size);

/**
 * @brief Delete the given neuron
 * 
 * @param neuron 
 */
void neuron_delete(neuron_t *neuron);

/**
 * @brief Initialises the neuron's values
 * 
 * @param neuron 
 */
void neuron_init(neuron_t *neuron);

#endif
