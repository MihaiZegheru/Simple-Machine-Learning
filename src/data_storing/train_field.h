/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#ifndef TRAIN_FIELD_H__
#define TRAIN_FIELD_H__

#include <stdlib.h>

typedef struct {
    float *data;
    size_t data_size;

    float result;
} train_field_t;

/**
 * @brief Instantiate a new train field and return it
 * 
 * @param data_size 
 * @return train_field_t* 
 */
train_field_t *train_field_new(size_t data_size);

/**
 * @brief Delete a provided train field
 * 
 * @param train_field 
 */
void train_field_delete(train_field_t *train_field);

#endif
