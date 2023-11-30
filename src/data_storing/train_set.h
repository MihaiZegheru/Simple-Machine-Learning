/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#ifndef TRAIN_SET_H__
#define TRAIN_SET_H__

#include <stdlib.h>

#include "train_field.h"

typedef struct {
    train_field_t **fields;
    size_t fields_size;

    size_t input_size;
} train_set_t;

train_set_t *train_set_new(size_t fields_size);
void train_set_delete(train_set_t *train_set);

#endif
