/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */
#ifndef NN_CONFIGURATION_H__
#define NN_CONFIGURATION_H__

typedef struct {
    size_t input_size;
    size_t *numbers_of_neurons_per_layer;
    size_t number_of_layers;
    size_t iterations;

    float (*activation_function)(float);

    float eps;
    float learning_rate;
} neural_network_configuration_t;

#endif