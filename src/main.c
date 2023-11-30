/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils/io_utils.h"
#include "utils/math_utils.h"
#include "neural_network/neural_network.h"

int main(void)
{
    srand(time(0)); 

    // Read the train set-------------------------------------------------------
    FILE *train_file;
    train_file = fopen("./res/train", "r");
    if (!train_file) {
        exit(-1);
    }
    train_set_t *train_set;
    fread_train_set(train_file, &train_set);
    fclose(train_file);
    // -------------------------------------------------------------------------

    // Set configuration--------------------------------------------------------
    neural_network_configuration_t configuration;
    configuration.eps = 1e-1;
    configuration.learning_rate = 1;
    configuration.iterations = 10000;
    configuration.input_size = train_set->input_size;
    configuration.number_of_layers = 2;
    configuration.activation_function = sigmoidf;

    configuration.numbers_of_neurons_per_layer =
            malloc(configuration.number_of_layers * sizeof(size_t));
    configuration.numbers_of_neurons_per_layer[0] = 10;
    configuration.numbers_of_neurons_per_layer
            [configuration.number_of_layers - 1] = 1;
    // ------------------------------------------------------------------------- 

    // Create a new neural network and train------------------------------------
    neural_network_t *neural_network = neural_network_new(&configuration);
    neural_network_init(neural_network);

    float cost = neural_network_cost(train_set, neural_network);
    printf("Initial cost: %f\n", cost);

    neural_network_train(train_set, neural_network);

    cost = neural_network_cost(train_set, neural_network);
    printf("Final cost: %f\n", cost);
    // -------------------------------------------------------------------------

    // Provide the input--------------------------------------------------------
    FILE *input_file;
    train_set_t *input_set;
    input_file = fopen("./res/input", "r");
    if (!input_file) {
        exit(-1);
    }
    fread_train_set(input_file, &input_set);
    
    neural_network_feed(input_set, neural_network);
    print_train_set(input_set);

    train_set_delete(input_set);
    fclose(input_file);
    // -------------------------------------------------------------------------
    
    neural_network_delete(neural_network);
    free(configuration.numbers_of_neurons_per_layer);
    train_set_delete(train_set);
    
    return 0;
}
