/*
 *   Copyright (c) 2023 Mihai Zegheru
 *   All rights reserved.
 */

#include "math_utils.h"

#include <math.h>

float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}
