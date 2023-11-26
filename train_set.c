/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "train_set.h"

#include <stdlib.h>

train_set_t *train_set_new(uint32_t size)
{
    train_set_t *train_set = malloc(sizeof(train_set_t *));
    if (!train_set) {
        exit(-1);
    }

    train_set->fields = malloc(size * sizeof(train_field_t));
    if (!train_set->fields) {
        exit(-1);
    }

    train_set->size = size;

    return train_set;
}

void train_set_delete(train_set_t *train_set)
{
    for (uint32_t i = 0; i < train_set->size; i++) {
        train_field_delete(&train_set->fields[i]);
    }

    free(train_set->fields);
    free(train_set);
}
