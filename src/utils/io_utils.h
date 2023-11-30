/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#ifndef IO_UTILS_H__
#define IO_UTILS_H__

#include <stdio.h>

#include "../data_storing/train_set.h"

/**
 * @brief Read a train field from the provided file
 * 
 * @param file 
 * @param data_size 
 * @param train_field 
 */
void fread_train_field(FILE *file, size_t data_size,
        train_field_t *train_field);

/**
 * @brief Read a train set from the provided file
 * 
 * @param file 
 * @param train_set 
 */
void fread_train_set(FILE *file, train_set_t **train_set);

/**
 * @brief Print a given train field
 * 
 * @param train_field 
 */
void print_train_field(train_field_t *train_field);

/**
 * @brief Print a given train set
 * 
 * @param train_set 
 */
void print_train_set(train_set_t *train_set);

#endif
