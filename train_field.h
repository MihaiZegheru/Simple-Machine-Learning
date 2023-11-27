/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#ifndef TRAIN_FIELD_H__
#define TRAIN_FIELD_H__

#include <stdint.h>

typedef struct {
float *data;
    uint32_t data_size;

    float result;
} train_field_t;

train_field_t *train_field_new(int32_t data_size);
void train_field_delete(train_field_t *train_field);

#endif