#include "neuron.h"

#include <stdlib.h>

neuron_t *neuron_new(size_t weights_size)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));

    neuron->weights = malloc(weights_size * sizeof(float));
    neuron->weights_size = weights_size;
}

void neuron_delete(neuron_t *neuron)
{
    free(neuron->weights);
    free(neuron);
}


void neuron_init(neuron_t *neuron)
{

}
