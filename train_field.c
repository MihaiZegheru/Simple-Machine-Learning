/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "train_field.h"

#include <stdlib.h>

train_field_t *train_field_new(int32_t data_size)
{
    train_field_t *train_field = malloc(sizeof(train_field_t));
    if (!train_field) {
        exit(-1);
    }

    train_field->data = malloc(data_size * sizeof(int32_t));
    if (!train_field->data) {
        exit(-1);
    }

    return train_field;
}

void train_field_delete(train_field_t *train_field)
{
    free(train_field->data);
    free(train_field);
}
