// in file: src/SparseMatrix.cpp
#include "SparseMatrix.hpp"
#include <stdexcept>
#include <iostream>

// Constructor Implementation
SparseMatrix::SparseMatrix(size_t num_rows, size_t num_cols, size_t capacity)
    : m_num_rows(num_rows), m_num_cols(num_cols) {
    
    m_values.reserve(capacity);
    m_col_indices.reserve(capacity);
    
    // row_offsets size is always (num_rows + 1). Initialize offsets to 0.
    m_row_offsets.resize(num_rows + 1, 0);
}

// Simplified setValue method (Assumes values are added in row-major order)
void SparseMatrix::setValue(size_t row, size_t col, double value) {
    if (row >= m_num_rows || col >= m_num_cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }

    m_values.push_back(value);
    m_col_indices.push_back(col);

    // Update the row offsets for all subsequent rows
    // This maintains the invariant that m_row_offsets[i] stores the total count of
    // non-zero elements encountered up to the end of row i-1.
    for (size_t i = row + 1; i <= m_num_rows; ++i) {
        m_row_offsets[i]++;
    }
}

// Core Operation: Matrix-Vector Multiplication (y = A * x)
Vector SparseMatrix::operator*(const Vector& x) const {
    if (m_num_cols != x.size()) {
        throw std::length_error("Matrix column count must match Vector size");
    }

    // Initialize the result vector (y)
    Vector result(m_num_rows);

    // Loop through each row of the matrix
    for (size_t i = 0; i < m_num_rows; ++i) {
        double sum = 0.0;
        
        // Determine the start and end index in the m_values array for this row (i)
        size_t start = m_row_offsets[i];
        size_t end   = m_row_offsets[i+1];

        // Loop through only the non-zero elements in the current row
        for (size_t k = start; k < end; ++k) {
            // Formula: sum += A_ik * x_k
            // m_values[k] is A_ik
            // m_col_indices[k] is the column index j (k)
            // x[m_col_indices[k]] is the corresponding element in the input vector x
            sum += m_values[k] * x[m_col_indices[k]];
        }
        
        result[i] = sum;
    }

    return result;
}
