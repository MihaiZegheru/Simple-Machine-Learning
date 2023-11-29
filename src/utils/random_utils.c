/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "random_utils.h"

#include <stdlib.h>

float random_float_normalised(void)
{
    return (float) rand() / RAND_MAX;
}
