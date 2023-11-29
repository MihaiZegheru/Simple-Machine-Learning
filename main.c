/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "io_utils.h"
#include "train_set.h"
#include "neural_network.h"

// TODO: write a config file loader as json

int main(void)
{
    setbuf(stdout, NULL);
    train_set_t *train_set;

    // Read the train set
    FILE *file;
    file = fopen("in", "r");
    fread_train_set(file, &train_set);
    fclose(file);

    srand(time(0)); 
    // srand(1);
    
    neural_network_configuration_t configuration;
    configuration.eps = 1e-2;
    configuration.learning_rate = 1e-1;
    configuration.iterations = 1000;
    configuration.input_size = train_set->input_size;
    configuration.number_of_layers = 2;

    configuration.numbers_of_neurons_per_layer =
            malloc(configuration.number_of_layers * sizeof(size_t));
    configuration.numbers_of_neurons_per_layer[0] = 10;
    configuration.numbers_of_neurons_per_layer
            [configuration.number_of_layers - 1] = 1;

    printf("AA");
    neural_network_t *neural_network = neural_network_new(&configuration);
    printf("AA");
    neural_network_init(neural_network);
    printf("AA");

    float cost = neural_network_cost(train_set, neural_network);
    printf("Initial cost: %f\n", cost);

    neural_network_train(train_set, neural_network);

    cost = neural_network_cost(train_set, neural_network);
    printf("Final cost: %f\n", cost);


    for (size_t i = 0; i < train_set->fields_size; i++) {
        train_field_t *train_field = train_set->fields[i];
        float result = neural_network_forward(train_field, neural_network);
        train_field->result = result;
        print_train_field(train_field);
    }

    neural_network_delete(neural_network);
    train_set_delete(train_set);
    
    return 0;
}
