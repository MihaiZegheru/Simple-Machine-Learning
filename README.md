
<!-- Copyright (c) 2023 Mihai Zegheru -->
<!-- All rights reserved. -->

# Simple-Machine-Learning
Simple machine learning program written in C, solely with the purpose of better
understanding the theory behind a machine learning model.

# How it works
The program simulates how all the components would affect the network, testing
the weights and biases individually. It shifts them by an epsilon value and then
computes the resulting cost and changes the model's values accordingly, using
the local slope of the cost function in order to find it's minimum.

This program is not efficient, especially as it does not use matrix operations.

# References
I got inspired by this [Tsoding's video](https://youtu.be/PGSba51aRYU).
