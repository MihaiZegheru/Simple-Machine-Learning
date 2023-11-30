/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "io_utils.h"

void fread_train_field(FILE *file, size_t data_size,
        train_field_t *train_field)
{
    train_field->data_size = data_size;

    for (size_t i = 0; i < data_size; i++) {
        fscanf(file, "%f", &(train_field->data[i]));
    }

    fscanf(file, "%f", &(train_field->result));
}

void fread_train_set(FILE *file, train_set_t **train_set)
{
    size_t fields_size;
    fscanf(file, "%u", &fields_size);

    *train_set = train_set_new(fields_size);

    size_t input_size;
    fscanf(file, "%u", &input_size);

    (*train_set)->input_size = input_size;

    for (size_t i = 0; i < fields_size; i++) {
        train_field_t *train_field = train_field_new(input_size);
        fread_train_field(file, input_size, train_field);

        (*train_set)->fields[i] = train_field;
    }
}

void print_train_field(train_field_t *train_field)
{
    for (size_t i = 0; i < train_field->data_size; i++) {
        printf("%f ", train_field->data[i]);
    }
    printf("%f\n", train_field->result);
}

void print_train_set(train_set_t *train_set)
{
    for (size_t i = 0; i < train_set->fields_size; i++) {
        print_train_field(train_set->fields[i]);
    }
}
