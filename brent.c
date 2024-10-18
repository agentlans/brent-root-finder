#include <math.h>
#include <float.h>
#include "brent.h"

// Function prototypes for forward declaration
void swap(double* x, double* y);
double compute_s(double a, double b, double c, double fa, double fb, double fc);
int should_bisect(double s, double a, double b, double c, double d, int mflag);
void update_interval(double* a, double* b, double* fa, double* fb, double s, double fs);

// Brent's root-finding method for function f
double brent(double (*f)(double, void*), double a, double b, void* params, 
             double tol, int max_iter, enum brent_error* error) {

    // Compute initial function values
    double fa = f(a, params);
    double fb = f(b, params);

    // Check if the root is bracketed
    if (fa * fb >= 0) {
        *error = BRENT_ERROR_NOT_BRACKETED;
        return NAN; // Return NaN to indicate failure
    }

    // Ensure |f(a)| >= |f(b)|
    if (fabs(fa) < fabs(fb)) {
        swap(&a, &b);
        swap(&fa, &fb);
    }

    double c = a; // Initialize c to a
    int mflag = 1; // Flag for bisection method
    double d = 0.0; // Previous step size

    for (int iter = 0; iter < max_iter; iter++) {
        double fc = f(c, params); // Evaluate f at c

        // Inverse quadratic interpolation or secant method
        double s = compute_s(a, b, c, fa, fb, fc);

        // Check conditions for s and apply bisection if necessary
        if (should_bisect(s, a, b, c, d, mflag)) {
            s = (a + b) / 2; // Bisection method
            mflag = 1; // Set mflag
        } else {
            mflag = 0; // Clear mflag
        }

        double fs = f(s, params); // Evaluate f at s

        // Update interval [a,b]
        update_interval(&a, &b, &fa, &fb, s, fs);

        // Ensure |f(a)| >= |f(b)| after each iteration
        if (fabs(fa) < fabs(fb)) {
            swap(&a, &b);
            swap(&fa, &fb);
        }

        // Check for convergence
        if ((fabs(b - a) < tol && fabs(fs) < tol) || fs == 0.0) {
            return s; // Return the root found within tolerance
        }
    }

    *error = BRENT_ERROR_MAX_ITERATIONS; // Indicate that max iterations were reached
    return NAN; // Return NaN to indicate failure to converge
}

// Helper function to swap two doubles
void swap(double* x, double* y) {
    double temp = *x;
    *x = *y;
    *y = temp;
}

// Compute the next guess for the root using inverse quadratic interpolation or secant method
double compute_s(double a, double b, double c, double fa, double fb, double fc) {
    double denom1 = (fa - fb);
    double denom2 = (fb - fc);

    if (fa != fb && fa != fc && fb != fc) {
        return (a * fb * fc * denom1 + b * fa * fc * (-denom1) + c * fa * fb * (fc - fa)) /
               ((denom1 * denom2) + (denom1 * denom2));
    }
    
    return b - fb * (b - a) / denom1;
}

// Determine whether to use the bisection method based on various conditions
int should_bisect(double s, double a, double b, double c, double d,
                  int mflag) {
    
    double lowerBound = (3 * a + b) / 4;
    double upperBound = b;
    
    return (s < lowerBound || s > upperBound ||
            (mflag && fabs(s - b) >= fabs(b - c) / 2) ||
            (!mflag && fabs(s - b) >= fabs(c - d) / 2));
}

// Update the interval [a,b] based on the value of s and fs
void update_interval(double* a, double* b,
                     double* fa, double* fb,
                     double s, double fs) {
    
    if (*fa * fs < 0) {
        *b = s; 
        *fb = fs;
    } else {
        *a = s; 
        *fa = fs;
    }
}
