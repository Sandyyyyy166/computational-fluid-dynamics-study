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

// --- Section 3: Implementation of the Rule of Five (Copy and Move Control) ---

// 1. Copy Constructor
// Purpose: Called when creating a new vector by copying an existing one (e.g., Vector v2 = v1;).
// It ensures a deep copy of the internal data is made.
Vector::Vector(const Vector& other) : m_data(other.m_data) {}

// 2. Copy Assignment Operator (using "Copy-and-Swap" Idiom)
// Purpose: Called when assigning one existing vector to another (e.g., v2 = v1;).
// This idiom is highly recommended as it provides a strong exception guarantee.
Vector& Vector::operator=(const Vector& other) {
    // Step 1: Create a temporary copy of the right-hand side (RHS).
    // This calls the Copy Constructor.
    Vector temp(other);

    // Step 2: Swap the current object's data (m_data) with the temporary object's data.
    // 'temp' now holds the original data of 'this' object.
    std::swap(m_data, temp.m_data);

    // Step 3: When 'temp' goes out of scope, it is automatically destroyed,
    // taking the original (old) data with it and safely cleaning up memory.
    return *this;
}

// 3. Move Constructor (C++11)
// Purpose: Called when an object is constructed from a temporary (r-value).
// This optimizes performance by "stealing" resources instead of copying.
Vector::Vector(Vector&& other) noexcept : m_data() {
    // Steal 'other's data by swapping our empty m_data with its m_data.
    std::swap(m_data, other.m_data);
    // 'other' is now empty and safe to destroy.
}

// 4. Move Assignment Operator (C++11)
// Purpose: Called when an existing object is assigned a temporary object.
Vector& Vector::operator=(Vector&& other) noexcept {
    // Check for self-assignment (though less critical with move semantics)
    if (this != &other) {
        // Swap our data with the temporary object's data.
        std::swap(m_data, other.m_data);
    }
    return *this;
}
