/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "neural_network.h"

#include <stdio.h>

neural_network_t *neural_network_new(size_t neuron_layers_size)
{
    // Add the output neuron
    neuron_layers_size++;
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

void neural_network_init(size_t input_size, size_t neuron_layers_size,
                         size_t *neurons_sizes,
                         neural_network_t *neural_network)
{
    if (neuron_layers_size + 1 != neural_network->neuron_layers_size) {
        // ERR: Number of neurons sizes not the same as neuron layers
        exit(-1);
    }

    for (size_t i = 0; i < neural_network->neuron_layers_size; i++) {
        neuron_layer_t *neuron_layer;
        if (i == neural_network->neuron_layers_size - 1) {
            neuron_layer = neuron_layer_new(1);
        } else {
            neuron_layer = neuron_layer_new(neurons_sizes[i]);
        }

        size_t weights_size = input_size;
        if (i) {
            weights_size = neurons_sizes[i - 1];
        }

        neuron_layer_init(weights_size, neuron_layer);

        neural_network->neuron_layers[i] = neuron_layer;
    }
}

float neural_network_forward(train_field_t *train_field,
              neural_network_t *neural_network)
{
    train_field_t *current_train_field = train_field;

    // Iterate through layers
    for (size_t i = 0; i < neural_network->neuron_layers_size; i++) {
        neuron_layer_t *neuron_layer = neural_network->neuron_layers[i];

        // Output of these layer neurons
        train_field_t *layer_result =
                train_field_new(neural_network->neuron_layers_size);
        // printf("A\n");
        // printf("%u\n", neuron_layer->neurons_size);
        // Iterate through neurons
        for (size_t j = 0; j < neuron_layer->neurons_size; j++) {
            neuron_t *neuron = neuron_layer->neurons[j];
        //             printf("B\n");
        // printf("%u %u\n", neuron->weights_size, current_train_field->data_size);
            if (neuron->weights_size != current_train_field->data_size) {
                // ERR: these should be equal
                // printf("CC");
                exit(-1);
            }

            float neuron_result = 0;
            for (size_t k = 0; k < neuron->weights_size; k++) {
                neuron_result += current_train_field->data[k] *
                                 neuron->weights[k];
            }
            neuron_result += neuron->bias;
            
            // TODO: Add activation function here

            layer_result->data[j] = neuron_result;
        }
        layer_result->data_size = neuron_layer->neurons_size;

        // train_field_delete(current_train_field);

        current_train_field = layer_result;
    }

    float result = current_train_field->data[0];

    train_field_delete(current_train_field);

    return result;
}

float neural_network_cost(train_set_t *train_set,
                         neural_network_t *neural_network)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_set->fields_size; i++) {
        printf("%u ", i);
        float y = neural_network_forward(train_set->fields[i], neural_network);
        float d = y - train_set->fields[i]->result;
        printf("%u ", i);
        result += d * d;
    }

    result /= train_set->fields_size;
    return result;
}

neural_network_t *neural_network_finite_difference
        (train_set_t *train_set, neural_network_t *neural_network)
{
    float eps = 1e-2;
    float c = neural_network_cost(train_set, neural_network);

    neural_network_t *aux_neural_network =
            neural_network_new(neural_network->neuron_layers_size - 1);

    size_t v[3] = {2, 3, 2};
    neural_network_init(2, 3, v, neural_network);


    for (size_t i = 0; i < neural_network->neuron_layers_size; i++) {
        neuron_layer_t *neuron_layer = neural_network->neuron_layers[i];
        neuron_layer_t *aux_neuron_layer = aux_neural_network->neuron_layers[i];

        // Iterate through neurons
        for (size_t j = 0; j < neuron_layer->neurons_size; j++) {
            neuron_t *neuron = neuron_layer->neurons[j];
            neuron_t *aux_neuron = aux_neuron_layer->neurons[j];

            for (size_t k = 0; k < neuron->weights_size; k++) {
                float saved = neuron->weights[k];
                neuron->weights[k] += eps;
                aux_neuron->weights[k] =
                    (neural_network_cost(train_set, neural_network) - c) / eps;
                neuron->weights[k] = saved;
            }

            float saved = neuron->bias;
            neuron->bias += eps;
            aux_neuron->bias =
                (neural_network_cost(train_set, neural_network) - c) / eps;
            neuron->bias = saved;
        }
    }

    return aux_neural_network;
}

void neural_network_learn(neural_network_t *aux_neural_network,
                          neural_network_t *neural_network)
{
    float rate = 1e-2;

    for (size_t i = 0; i < neural_network->neuron_layers_size; i++) {
        neuron_layer_t *neuron_layer = neural_network->neuron_layers[i];
        neuron_layer_t *aux_neuron_layer = aux_neural_network->neuron_layers[i];

        // Iterate through neurons
        for (size_t j = 0; j < neuron_layer->neurons_size; j++) {
            neuron_t *neuron = neuron_layer->neurons[j];
            neuron_t *aux_neuron = aux_neuron_layer->neurons[j];

            for (size_t k = 0; k < neuron->weights_size; k++) {
                neuron->weights[k] -= rate * aux_neuron->weights[k];
            }
            neuron->bias -= rate * aux_neuron->bias;
        }
    }
}

// void train(train_set_t *train_set, neural_network_t *neural_network)
// {
//     for (size_t i = 0; i < train_set->fields_size; i++) {
//         train_field_t *train_field = train_set->fields[i];
//         for (size_t j = 0; j < train_set->data_size; j++) {
            
//             neuron_layer_t *neuron_layer = neural_network->neuron_layers[0];

//             for (size_t k = 0; k < neuron_layer->neurons_size; k++) {
//                 neuron_t *neuron = neuron_layer->neurons[k];

//                 // float 
//             }
//         }
//     }
// }


