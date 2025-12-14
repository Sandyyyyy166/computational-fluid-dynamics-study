#include "cfd.hpp"
#include "SparseMatrix.hpp"
#include "vector.hpp"
#include <iostream>
#include <cmath>
#include <numeric> // For std::inner_product (or you can use a loop for dot product)

// The function's actual definition/implementation.
void hello_cfd() {
    std::cout << "Hello from the CFD library! The project is alive." << std::endl;
}

// Helper function: Calculate Dot Product (Vector a · Vector b)
// This is often a separate function for clarity or put inside the Vector class
double dot_product(const Vector& a, const Vector& b) {
    if (a.size() != b.size()) {
        throw std::length_error("Vectors must be same size for dot product.");
    }
    
    double result = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

// Helper function: Calculate the L2 Norm (||a||)
double norm(const Vector& a) {
    return std::sqrt(dot_product(a, a));
}


// --- Conjugate Gradient Solver Implementation ---
Vector solve_cg(const SparseMatrix& A, const Vector& b, const Vector& x0, 
                size_t max_iter, double tolerance) {
    
    // 1. Initialization (Guess is our starting point)
    Vector x = x0; 
    
    // r = b - A * x (Residual: How far off our guess is)
    Vector r = b - (A * x); 
    
    // p = r (Initial search direction is the residual)
    Vector p = r; 

    // Initial check on the error (residual norm)
    double r_norm = norm(r);

    std::cout << "CG Solver started. Initial residual norm: " << r_norm << std::endl;
    
    // r_old_dot_r_old = r · r (The numerator for alpha and beta)
    double r_old_dot_r_old = dot_product(r, r);
    
    // Base residual norm for relative tolerance check
    double b_norm = norm(b);

    // 2. Iterative Loop
    for (size_t k = 0; k < max_iter; ++k) {
        
        // Check for convergence based on tolerance
        if (r_norm < tolerance * b_norm) {
            std::cout << "CG converged in " << k << " iterations. Final residual norm: " << r_norm << std::endl;
            return x;
        }

        // a) Ap = A * p (Matrix-Vector product with the search direction)
        Vector Ap = A * p;

        // b) Calculate alpha (The optimal step size along direction p)
        // alpha = (r_old · r_old) / (p · Ap)
        double alpha = r_old_dot_r_old / dot_product(p, Ap);

        // c) Update solution: x = x + alpha * p
        // Note: alpha * p requires the Vector::operator* (scalar multiplication)
        x = x + (p * alpha); 

        // d) Update residual: r_new = r_old - alpha * Ap
        Vector r_new = r - (Ap * alpha);
        
        // e) Calculate new residual norm for convergence check
        r_norm = norm(r_new);
        std::cout << "Iteration " << k + 1 << ": Residual norm = " << r_norm << std::endl;
        
        // f) Calculate beta (The factor to define the next search direction)
        // beta = (r_new · r_new) / (r_old · r_old)
        double r_new_dot_r_new = dot_product(r_new, r_new);
        double beta = r_new_dot_r_new / r_old_dot_r_old;

        // g) Update search direction: p_new = r_new + beta * p_old
        // Note: beta * p_old requires the Vector::operator* (scalar multiplication)
        p = r_new + (p * beta);

        // h) Prepare for next iteration
        r = r_new; // r_new becomes r_old for the next iteration
        r_old_dot_r_old = r_new_dot_r_new;
    }
    
    // If loop finished without converging
    std::cout << "CG FAILED to converge in max_iter (" << max_iter << ") iterations. Final residual norm: " << r_norm << std::endl;
    return x;
}
