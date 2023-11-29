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

train_field_t *train_field_new(size_t data_size);
void train_field_delete(train_field_t *train_field);

#endif