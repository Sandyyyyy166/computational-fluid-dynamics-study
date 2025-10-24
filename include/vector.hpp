// in file: include/vector.hpp
#pragma once

#include <vector>  // For using std::vector internally
#include <cstddef> // For using size_t, which is the standard type for array indexing and sizes

/**
 * @class Vector
 * @brief A custom Vector class designed for linear algebra operations.
 *
 * This class provides a fixed-size vector implementation that uses
 * std::vector for its underlying data storage. It's designed to
 * be intuitive for mathematical operations by overloading common
 * arithmetic operators.
 */
class Vector {
public:
    // --- 1. Constructors (The "birth" of an object) ---

    /**
     * @brief Default constructor. Creates an empty vector of size 0.
     */
    Vector();

    /**
     * @brief Creates a vector of a specific size, initialized with zeros.
     * @param size The number of elements in the vector.
     */
    Vector(size_t size);

    /**
     * @brief Creates a vector from an existing std::vector of doubles.
     * @param data The std::vector to copy data from.
     */
    Vector(const std::vector<double>& data);


    // --- 2. The Rule of Three/Five (Managing copies and memory) ---

    /**
     * @brief Destructor.
     */
    ~Vector();

    /**
     * @brief Copy constructor. Creates a deep copy of another vector.
     * @param other The vector to be copied.
     */
    Vector(const Vector& other);

    /**
     * @brief Copy assignment operator (using the copy-and-swap idiom).
     * @param other The vector to assign from.
     * @return A reference to this instance.
     */
    Vector& operator=(const Vector& other);

    /**
     * @brief (C++11) Move constructor.
     * @param other The vector to be moved from.
     */
    Vector(Vector&& other) noexcept; // noexcept keyword is a promise it won't throw exceptions

    /**
     * @brief (C++11) Move assignment operator.
     * @param other The vector to be move-assigned from.
     * @return A reference to this instance.
     */
    Vector& operator=(Vector&& other) noexcept;


    // --- 3. Public Methods / API (The "interface") ---

    /**
     * @brief Gets the number of elements in the vector.
     * @return The size of the vector.
     * 'const' here means this function promises not to change the object.
     */
    size_t size() const;


    // --- 4. Operator Overloading (Making the class intuitive) ---

    /**
     * @brief Accesses an element for reading or writing.
     * @param index The index of the element to access.
     * @return A reference to the element at the specified index.
     */
    double& operator[](size_t index);

    /**
     * @brief Accesses an element for reading only (const-qualified version).
     * @param index The index of the element to access.
     * @return A const reference to the element.
     */
    const double& operator[](size_t index) const;

    /**
     * @brief Vector addition.
     * @param rhs The vector on the "right-hand side" of the + operator.
     * @return A new Vector object that is the sum of the two vectors.
     */
    Vector operator+(const Vector& rhs) const;

    /**
     * @brief Vector subtraction.
     * @param rhs The vector on the "right-hand side" of the - operator.
     * @return A new Vector object that is the result of the subtraction.
     */
    Vector operator-(const Vector& rhs) const;

    /**
     * @brief Scalar multiplication (vector * scalar).
     * @param scalar The scalar value to multiply by.
     * @return A new Vector object where each element is multiplied by the scalar.
     */
    Vector operator*(double scalar) const;


private:
    // --- 5. Private Member Variables ---

    // The internal data storage. We use std::vector because it handles
    // all the difficult memory management (allocation/deallocation) for us.
    std::vector<double> m_data;
};