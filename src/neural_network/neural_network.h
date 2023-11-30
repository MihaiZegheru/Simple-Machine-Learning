/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#ifndef NEURAL_NETWORK_H__
#define NEURAL_NETWORK_H__

#include <stdlib.h>

#include "neural_network_configuration.h"
#include "neuron_layer.h"
#include "../data_storing/train_set.h"
#include "../data_storing/train_field.h"

typedef struct {
    neuron_layer_t **neuron_layers;
    size_t neuron_layers_size;

    neural_network_configuration_t *neural_network_configuration;
} neural_network_t;

/**
 * @brief Instantiate a new neural network and return it
 * 
 * @param neural_network_configuration 
 * @return neural_network_t* 
 */
neural_network_t *neural_network_new(
        neural_network_configuration_t *neural_network_configuration);

/**
 * @brief Delete a provided neural network
 * 
 * @param neural_network 
 */
void neural_network_delete(neural_network_t *neural_network);

/**
 * @brief Propagates through the neural network and initialises its values
 * 
 * @param neural_network 
 */
void neural_network_init(neural_network_t *neural_network);

/**
 * @brief Feed a train field into the neural network and return the result
 * 
 * @param train_field 
 * @param neural_network 
 * @return float 
 */
float neural_network_forward(train_field_t *train_field,
        neural_network_t *neural_network);

/**
 * @brief Check the neural network's cost for a provided train set and return it
 * 
 * @param train_set 
 * @param neural_network 
 * @return float 
 */
float neural_network_cost(train_set_t *train_set,
        neural_network_t *neural_network);

/**
 * @brief Performs operations on the neural network by shifting each weight and
 *        bias and computing the difference between the expected result and the
 *        actual result
 * 
 * @param train_set 
 * @param aux_neural_network 
 * @param neural_network 
 */
void neural_network_compute_difference(train_set_t *train_set,
        neural_network_t *aux_neural_network, neural_network_t *neural_network);

/**
 * @brief Updates the values of the neural network by previously performed
 *        operations
 * 
 * @param aux_neural_network 
 * @param neural_network 
 */
void neural_network_learn(neural_network_t *aux_neural_network,
        neural_network_t *neural_network);

/**
 * @brief Trains the neural network on the provided train set
 * 
 * @param train_set 
 * @param neural_network 
 */
void neural_network_train(train_set_t *train_set,
        neural_network_t *neural_network);

/**
 * @brief Feeds the neural network data for it to predict
 * 
 * @param input_set 
 * @param neural_network 
 */
void neural_network_feed(train_set_t *input_set,
        neural_network_t *neural_network);

#endif
