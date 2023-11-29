#ifndef NN_CONFIGURATION_H__
#define NN_CONFIGURATION_H__

typedef struct {
    size_t input_size;
    size_t number_of_layers;
    size_t *numbers_of_neurons_per_layer;

    float eps;
    float learning_rate;
} nn_configuration_t;

#endif