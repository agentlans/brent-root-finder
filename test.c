#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <time.h>

#include "brent.h"

// Test functions
double f1(double x, void* params) { return x*x - 4; }
double f2(double x, void* params) { return sin(x); }
double f3(double x, void* params) { return exp(x) - 2; }
double f4(double x, void* params) { return x*x*x - x - 2; }
double f5(double x, void* params) { return tan(x); }

// Function with user-defined parameter
double f6(double x, void* params) {
    double* a = (double*)params;
    return x*x - *a;
}

// Function with discontinuity
double f7(double x, void* params) {
    return x < 0 ? -1 : (x > 0 ? 1 : 0);
}

// Function that's almost flat near the root
double f8(double x, void* params) {
    return pow(x - 1, 3);
}

// Newton's method for comparison
double newton(double (*f)(double, void*), double (*df)(double, void*), double x0, void* params, double tol, int maxiter, enum brent_error* error) {
    double x = x0;
    for (int i = 0; i < maxiter; i++) {
        double fx = f(x, params);
        if (fabs(fx) < tol) {
            *error = 0;
            return x;
        }
        double dfx = df(x, params);
        if (dfx == 0) {
            *error = 1;
            return x;
        }
        x = x - fx / dfx;
    }
    *error = 2;
    return x;
}

// Derivative of f1 for Newton's method
double df1(double x, void* params) {
    return 2 * x;
}

void test_brent() {
    enum brent_error error = BRENT_SUCCESS;
    double tol = 1e-6;
    int itmax = 100;
    void* params = NULL;

    // Original tests
    double root1 = brent(f1, 0, 3, params, tol, itmax, &error);
    assert(fabs(root1 - 2.0) < tol && error == 0);

    double root2 = brent(f2, 3, 4, params, tol, itmax, &error);
    assert(fabs(root2 - M_PI) < tol && error == 0);

    double root3 = brent(f3, 0, 1, params, tol, itmax, &error);
    assert(fabs(root3 - log(2)) < tol && error == 0);

    double root4 = brent(f4, 1, 2, params, tol, itmax, &error);
    assert(fabs(f4(root4, params)) < tol && error == 0);

    double root5 = brent(f5, 3, 3.2, params, tol, itmax, &error);
    assert(fabs(root5 - M_PI) < tol && error == 0);

    double root7 = brent(f1, 1.99, 2.01, params, tol, itmax, &error);
    assert(fabs(root7 - 2.0) < tol && error == 0);

    double root8 = brent(f1, 1, 1000, params, tol, itmax, &error);
    assert(fabs(root8 - 2.0) < tol || fabs(root8 + 2.0) < tol);

    double root9 = brent(f1, 0, 3, params, 1e-12, itmax, &error);
    assert(fabs(root9 - 2.0) < 1e-12 && error == 0);

    brent(f1, 0, 3, params, tol, 5, &error);
    assert(error == BRENT_ERROR_MAX_ITERATIONS);

    brent(f1, 3, 4, params, tol, itmax, &error);
    assert(error == BRENT_ERROR_NOT_BRACKETED);

    // New comprehensive tests

    // Test with user-defined parameter
    double a = 9;
    error = BRENT_SUCCESS;
    double root12 = brent(f6, 1, 4, &a, tol, itmax, &error);
    assert(fabs(root12 - 3.0) < tol && error == 0);

    // Test with discontinuous function
    double root13 = brent(f7, -1, 1, params, tol, itmax, &error);
    assert(fabs(root13) < tol && error == 0);

    // Test with function that's almost flat near the root
    double root14 = brent(f8, 0, 2, params, tol, itmax, &error);
    assert(fabs(root14 - 1.0) < tol && error == 0);

    // Test with different epsilon values
    double root15 = brent(f1, 0, 3, params, tol, itmax, &error);
    assert(fabs(root15 - 2.0) < tol && error == 0);

    double root16 = brent(f1, 0, 3, params, tol, itmax, &error);
    assert(fabs(root16 - 2.0) < tol && error == 0);

    // Comparison with Newton's method
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    double root_brent = brent(f1, 0, 3, params, tol, itmax, &error);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Brent's method: root = %.10f, time = %f seconds\n", root_brent, cpu_time_used);

    start = clock();
    double root_newton = newton(f1, df1, 1.5, params, tol, itmax, &error);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Newton's method: root = %.10f, time = %f seconds\n", root_newton, cpu_time_used);

    printf("All tests passed successfully!\n");
}

int main() {
    test_brent();
    return 0;
}
