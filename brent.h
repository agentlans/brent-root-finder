#ifndef _BRENTH
#define _BRENTH

/**
 * @enum brent_error
 * @brief Error codes for the Brent's method function.
 *
 * This enumeration defines the possible error states that can be returned 
 * by the Brent's method implementation.
 */
enum brent_error {
    BRENT_SUCCESS = 0,                /**< Indicates successful execution. */
    BRENT_ERROR_NOT_BRACKETED = 1,    /**< Indicates that the root is not bracketed. */
    BRENT_ERROR_MAX_ITERATIONS = 2     /**< Indicates that the maximum number of iterations was reached. */
};

/**
 * @brief Finds a root of a function using Brent's method.
 *
 * This function implements Brent's method for root finding, which combines 
 * bisection, secant, and inverse quadratic interpolation methods. It requires 
 * that the function values at the endpoints of the interval have opposite signs.
 *
 * @param f A pointer to the function to be evaluated. It should take a double 
 *          and a void pointer as parameters and return a double.
 * @param a The starting point of the interval (left endpoint).
 * @param b The ending point of the interval (right endpoint).
 * @param params A pointer to additional parameters to be passed to the function 
 *                being evaluated.
 * @param tol The tolerance for convergence; the algorithm stops when the width 
 *            of the interval is less than this value or when the function value 
 *            is sufficiently close to zero.
 * @param max_iter The maximum number of iterations allowed for convergence.
 * @param error A pointer to an enum brent_error variable where error codes will 
 *               be stored if an error occurs during execution.
 *
 * @return The root found within tolerance if successful; otherwise, NaN is returned 
 *         to indicate failure. If an error occurs, `error` will be set accordingly.
 */
double brent(double (*f)(double, void*), double x1, double x2, void* params, 
             double tol, int itmax, enum brent_error* error);

#endif