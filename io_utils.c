/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "io_utils.h"

void fread_train_field(FILE *file, uint32_t data_size,
                       train_field_t *train_field)
{
    for (uint32_t i = 0; i < data_size; i++) {
        fscanf(file, "%d", &(train_field->data[i]));
    }

    fscanf(file, "%d", &(train_field->result));
}

void fread_train_set(FILE *file, train_set_t **train_set)
{
    uint32_t size;
    fscanf(file, "%d", &size);

    *train_set = train_set_new(size);

    uint32_t data_size;
    fscanf(file, "%d", &data_size);
    (*train_set)->data_size = data_size;

    for (uint32_t i = 0; i < size; i++) {
        train_field_t *train_field = train_field_new(data_size);
        fread_train_field(file, data_size, train_field);

        (*train_set)->fields[i] = train_field;
    }
}
