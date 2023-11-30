/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "neuron.h"

#include <stdlib.h>

#include "../utils/random_utils.h"

neuron_t *neuron_new(size_t weights_size)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));
    if (!neuron) {
        exit(-1);
    }

    neuron->weights_size = weights_size;
    neuron->weights = malloc(weights_size * sizeof(float));
    if (!neuron->weights) {
        exit(-1);
    }
    

    return neuron;
}

void neuron_delete(neuron_t *neuron)
{
    free(neuron->weights);
    free(neuron);
}

void neuron_init(neuron_t *neuron)
{
    for (size_t i = 0; i < neuron->weights_size; i++) {
        neuron->weights[i] = random_float_normalised();
    }
    neuron->bias = random_float_normalised();
}
