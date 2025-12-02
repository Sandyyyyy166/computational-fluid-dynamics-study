// in file: include/SparseMatrix.hpp
#pragma once

#include <vector>
#include <cstddef>
#include "vector.hpp" // Dependency: The Matrix operates on the Vector class

class SparseMatrix {
public:
    // Constructor: Creates an NxM matrix, reserving space for non-zero elements
    SparseMatrix(size_t num_rows, size_t num_cols, size_t capacity);

    // Modifies the matrix structure (Simplified CSR construction)
    void setValue(size_t row, size_t col, double value);

    // Core Operation: Matrix multiplied by a Vector (result = A * x)
    Vector operator*(const Vector& x) const;

private:
    // --- CSR Format Data Storage ---
    size_t m_num_rows;
    size_t m_num_cols;
    
    // 1. Stores all non-zero values
    std::vector<double> m_values;      
    // 2. Stores the column index for each value in m_values
    std::vector<size_t> m_col_indices; 
    // 3. Stores the starting index for each row in m_values (the "bookmarks")
    std::vector<size_t> m_row_offsets; 
};
