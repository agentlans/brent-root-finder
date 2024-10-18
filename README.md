# Brent's Method Root Finder

This repository contains an implementation of Brent's method for finding roots of functions in C. Brent's method is a root-finding algorithm that combines the bisection method, secant method, and inverse quadratic interpolation to efficiently locate roots of continuous functions.

## Overview

The implementation includes:
- **`brent.c`**: The source code for the Brent's method algorithm.
- **`brent.h`**: The header file containing function declarations and error codes.
- **`test.c`**: A test program to demonstrate the usage of the Brent's method.
- **`Makefile`**: A makefile to compile the project easily.

## Features

- **Robustness**: Brent's method combines multiple root-finding techniques for improved performance.
- **Error Handling**: Provides error codes to indicate the status of the root-finding process.
- **Customizable**: Allows passing additional parameters to the function being evaluated.

## Installation

To build the project, ensure you have a C compiler installed (like `gcc`). Clone the repository and navigate into it:

```bash
git clone https://github.com/agentlans/brent-root-finder.git
cd brent-root-finder
```

Then, compile the project using:

```bash
make
```

This will generate an executable named `test_program` which will run the test cases.

## Usage

To use Brent's method, you need to define a function that matches the expected signature. Here’s an example of how to implement and use it:

```c
#include <stdio.h>
#include <math.h>

#include "brent.h"

double my_function(double x, void* params) {
    return x * x - 2; // Example: Finding the square root of 2
}

int main() {
    enum brent_error error;
    double root = brent(my_function, 0.0, 2.0, NULL, 1e-6, 100, &error);

    if (error == BRENT_SUCCESS) {
        printf("Root found: %f\n", root);
    } else {
        printf("Error occurred: %d\n", error);
    }

    return 0;
}
```

Compile the source code and `brent.c` and run the program. This will execute your example function using Brent's method and display the result.

## Error Codes

The `enum brent_error` provides the following error codes:

- `BRENT_SUCCESS`: The operation was successful.
- `BRENT_ERROR_NOT_BRACKETED`: The provided interval does not bracket a root.
- `BRENT_ERROR_MAX_ITERATIONS`: The maximum number of iterations was reached without convergence.

## Author, License

Copyright :copyright: 2024 by Alan Tseng

MIT License
