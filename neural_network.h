/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#ifndef NEURAL_NETWORK_H__
#define NEURAL_NETWORK_H__

#include <stdlib.h>

#include "neuron_layer.h"
#include "train_set.h"
#include "train_field.h"
#include "neural_network_configuration.h"

typedef struct {
    neuron_layer_t **neuron_layers;
    size_t neuron_layers_size;

    neural_network_configuration_t *neural_network_configuration;
} neural_network_t;


neural_network_t *neural_network_new(
        neural_network_configuration_t *neural_network_configuration);
void neural_network_delete(neural_network_t *neural_network);
void neural_network_init(neural_network_t *neural_network);

float neural_network_forward(train_field_t *train_field,
        neural_network_t *neural_network);
float neural_network_cost(train_set_t *train_set,
        neural_network_t *neural_network);
void neural_network_finite_difference(train_set_t *train_set,
        neural_network_t *aux_neural_network, neural_network_t *neural_network);
void neural_network_learn(neural_network_t *aux_neural_network,
        neural_network_t *neural_network);
void neural_network_train(train_set_t *train_set,
        neural_network_t *neural_network);

#endif
