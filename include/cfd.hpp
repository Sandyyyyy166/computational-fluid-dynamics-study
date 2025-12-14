#pragma once

// in file: include/cfd.hpp

#include "SparseMatrix.hpp"
#include "vector.hpp"
#include <cmath> // so we can use square root

void hello_cfd();

// --- Helper Functions Declaration ---
double dot_product(const Vector& a, const Vector& b);
double norm(const Vector& a);

// The Conjugate Gradient Solver Function
Vector solve_cg(const SparseMatrix& A, const Vector& b, const Vector& x0, size_t max_iter, double tolerance);


