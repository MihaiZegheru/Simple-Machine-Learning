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

// float random_float(void)
// {
//     return (float) rand() / RAND_MAX;
// }

// float sigmoidf(float x)
// {
//     return 1.f / (1.f + expf(-x));
// }

// float cost(float w, float b, train_set_t *train_set) {
//     // y = x * w + b, where x is the fed data
//     float result = 0.f;
//     for (size_t i = 0; i < train_set->fields_size; i++) {
//         float x = train_set->fields[i]->data[0];
//         float y = sigmoidf(x * w + b);
//         float d = y - train_set->fields[i]->result;
//         result += d * d;
//     }

//     result /= train_set->fields_size;
    
//     return result;
// }

int main(void)
{
    setbuf(stdout, NULL);
    train_set_t *train_set;

    // Read the train set
    FILE *file;
    file = fopen("in", "r");
    fread_train_set(file, &train_set);
    fclose(file);

    // srand(time(0)); 
    srand(1);

    size_t v[1] = {2};
    neural_network_t *neural_network = neural_network_new(2, 1, v);

    float cost = neural_network_cost(train_set, neural_network);
    printf("Initial cost: %f\n", cost);

    for (size_t i = 0; i < 100000; i++) {
        neural_network_t *aux_neural_network =
                neural_network_finite_difference(train_set, neural_network);

        neural_network_learn(aux_neural_network, neural_network);

        neural_network_delete(aux_neural_network);
    }

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
