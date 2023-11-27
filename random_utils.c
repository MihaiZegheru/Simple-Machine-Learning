/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "random_utils.h"

#include <stdlib.h>
#include <stdio.h>
float random_float_normalised(void)
{
    // printf("%f\n", (float) rand() / RAND_MAX);
    return (float) rand() / RAND_MAX;
}
