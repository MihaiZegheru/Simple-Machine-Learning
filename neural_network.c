/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "neural_network.h"

#include <stdio.h>
#include "io_utils.h"
#include "math_utils.h"

neural_network_t *neural_network_new(
        neural_network_configuration_t *configuration)
{
    neural_network_t *neural_network = malloc(sizeof(neural_network_t));
    if (!neural_network) {
        exit(-1);
    }

    neural_network->neural_network_configuration = configuration;
    neural_network->neuron_layers_size = configuration->number_of_layers;

    // Add the output neuron
    neural_network->neuron_layers = malloc(neural_network->neuron_layers_size *
            sizeof(neuron_layer_t *));
    if (!neural_network->neuron_layers) {
        exit(-1);
    }

    // Check if last layer is of size 1
    size_t number_of_layers = configuration->number_of_layers;
    if (configuration->
            numbers_of_neurons_per_layer[number_of_layers - 1] != 1) {
        exit(-1);
    }
    
    return neural_network;
}

void neural_network_delete(neural_network_t *neural_network)
{
    for (size_t i = 0; i < neural_network->neuron_layers_size; i++) {
        neuron_layer_delete(neural_network->neuron_layers[i]);
    }
    free(neural_network->neuron_layers);
    free(neural_network);
}


void neural_network_init(neural_network_t *neural_network)
{
    neural_network_configuration_t *configuration =
            neural_network->neural_network_configuration;

    for (size_t i = 0; i < configuration->number_of_layers; i++) {
        neuron_layer_t *neuron_layer = neuron_layer_new(configuration->
                numbers_of_neurons_per_layer[i]);
        neural_network->neuron_layers[i] = neuron_layer;

        size_t weights_size = configuration->input_size;
        if (i) {
            weights_size = configuration->numbers_of_neurons_per_layer[i - 1];
        }

        neuron_layer_init(weights_size, neuron_layer);
    }
}

float neural_network_forward(train_field_t *train_field,
        neural_network_t *neural_network)
{
    train_field_t *current_train_field = train_field;
    float (*activation_function)(float) =
            neural_network->neural_network_configuration->activation_function;

    // Iterate through layers
    for (size_t i = 0; i < neural_network->neuron_layers_size; i++) {
        neuron_layer_t *neuron_layer = neural_network->neuron_layers[i];

        // Output of these layer neurons
        train_field_t *layer_result =
                train_field_new(neuron_layer->neurons_size);

        // Iterate through neurons
        for (size_t j = 0; j < neuron_layer->neurons_size; j++) {
            neuron_t *neuron = neuron_layer->neurons[j];
            if (neuron->weights_size != current_train_field->data_size) {
                exit(-1);
            }

            float neuron_result = 0;

            // Iterate through weights
            for (size_t k = 0; k < neuron->weights_size; k++) {
                neuron_result += current_train_field->data[k] *
                        neuron->weights[k];
            }
            neuron_result += neuron->bias;
            layer_result->data[j] = activation_function(neuron_result);
        }
        layer_result->data_size = neuron_layer->neurons_size;

        if (current_train_field != train_field) {
            train_field_delete(current_train_field);
        }
        current_train_field = layer_result;
    }

    float result = current_train_field->data[0];

    if (current_train_field != train_field) {
        train_field_delete(current_train_field);
    }

    return result;
}

float neural_network_cost(train_set_t *train_set,
        neural_network_t *neural_network)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_set->fields_size; i++) {
        float y = neural_network_forward(train_set->fields[i], neural_network);
        float d = y - train_set->fields[i]->result;

        result += d * d;
    }
    result /= train_set->fields_size;

    return result;
}

void neural_network_compute_difference(train_set_t *train_set,
        neural_network_t *aux_neural_network, neural_network_t *neural_network)
{
    float eps = neural_network->neural_network_configuration->eps;

    float c = neural_network_cost(train_set, neural_network);

    // Iterate through layers
    for (size_t i = 0; i < neural_network->neuron_layers_size; i++) {
        neuron_layer_t *neuron_layer = neural_network->neuron_layers[i];
        neuron_layer_t *aux_neuron_layer = aux_neural_network->neuron_layers[i];

        // Iterate through neurons
        for (size_t j = 0; j < neuron_layer->neurons_size; j++) {
            neuron_t *neuron = neuron_layer->neurons[j];
            neuron_t *aux_neuron = aux_neuron_layer->neurons[j];

            // Iterate through weights
            for (size_t k = 0; k < neuron->weights_size; k++) {
                float saved = neuron->weights[k];
                neuron->weights[k] += eps;

                aux_neuron->weights[k] = (neural_network_cost(train_set,
                        neural_network) - c) / eps;
                neuron->weights[k] = saved;
            }

            float saved = neuron->bias;
            neuron->bias += eps;
            aux_neuron->bias = (neural_network_cost(train_set,
                    neural_network) - c) / eps;
            neuron->bias = saved;
        }
    }
}

void neural_network_learn(neural_network_t *aux_neural_network,
        neural_network_t *neural_network)
{
    float rate = neural_network->neural_network_configuration->learning_rate;

    // Iterate through layers
    for (size_t i = 0; i < neural_network->neuron_layers_size; i++) {
        neuron_layer_t *neuron_layer = neural_network->neuron_layers[i];
        neuron_layer_t *aux_neuron_layer = aux_neural_network->neuron_layers[i];

        // Iterate through neurons
        for (size_t j = 0; j < neuron_layer->neurons_size; j++) {
            neuron_t *neuron = neuron_layer->neurons[j];
            neuron_t *aux_neuron = aux_neuron_layer->neurons[j];

            // Iterate through weights
            for (size_t k = 0; k < neuron->weights_size; k++) {
                neuron->weights[k] -= rate * aux_neuron->weights[k];
            }
            neuron->bias -= rate * aux_neuron->bias;
        }
    }
}

void neural_network_train(train_set_t *train_set,
        neural_network_t *neural_network)
{

    neural_network_configuration_t *configuration =
            neural_network->neural_network_configuration;

    size_t iterations = configuration->iterations;
    
    for (size_t i = 0; i < iterations; i++) {
        neural_network_t *aux_neural_network = 
                neural_network_new(configuration);
        neural_network_init(aux_neural_network);

        neural_network_compute_difference(train_set, aux_neural_network,
                neural_network);
        neural_network_learn(aux_neural_network, neural_network);

        neural_network_delete(aux_neural_network);
    }
}
