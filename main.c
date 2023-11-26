/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "io_utils.h"
#include "train_set.h"

float random_float(void)
{
    return (float) rand() / RAND_MAX;
}

float cost(float w, float b, train_set_t *train_set) {
    // y = x * w + b, where x is the fed data
    float result = 0.0f;
    for (size_t i = 0; i < train_set->size; i++) {
        float x = train_set->fields[i]->data[0];
        float y = x * w + b;
        float d = y - train_set->fields[i]->result;
        result += d * d;
    }

    result /= train_set->size;
    
    return result;
}

int main(void)
{
    train_set_t *train_set;

    // Read the train set
    FILE *file;
    file = fopen("in", "r");
    fread_train_set(file, &train_set);
    fclose(file);

    // srand(time(0)); 
    srand(1);
    
    float w = random_float();
    float b = random_float();

    float EPS = 1e-3;
    float RATE = 1e-3;

    for (size_t i = 0; i < 10000; i++) {
        float c = cost(w, b, train_set);
        printf("w = %f, b = %f, c = %f\n", w, b, c);

        float dw = (cost(w + EPS, b, train_set) - cost(w, b, train_set)) / EPS;
        float db = (cost(w, b + EPS, train_set) - cost(w, b, train_set)) / EPS;

        w -= RATE * dw;
        b -= RATE * db;
    }

    train_set_delete(train_set);
    
    return 0;
}
