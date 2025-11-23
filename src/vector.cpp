// in file: src/vector.cpp

// 1. Include the corresponding header file.
// This links the "menu" (header) with this "recipe" (source).
#include "vector.hpp"

// 2. Include necessary standard libraries.
#include <stdexcept> // For throwing errors (e.g., size mismatch)
#include <algorithm> // For std::swap

// --- Section 1: Implementation of Constructors ---

// Default Constructor  
// Initialise the vector with a size of 0.
// We use the member initialiser list to initialise m_data.
Vector::Vector() : m_data() {} // Scope Resolution Operator

// Constructor with size
// Initialise m_data with specific 'size' and fills it with 0.0.
Vector::Vector(size_t size) : m_data(size, 0.0) {} // Member Initialiser List

// Constructor from std::vector
// Copies the existing data from the input std::vector to our m_data.
Vector::Vector(const std::vector<double>& data) : m_data(data) {}

// --- Section 2: Implementation of Destructor ---

// Destructor
// Since we use std::vector for storage, it manages memory automatically.
// We don't need to manually 'delete' anything here.
Vector::~Vector() {}