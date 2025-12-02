#include "cfd.hpp" // We include the library's public menu

//int main() {
    // We call the function from the library
    //hello_cfd();
    //return 0;
//}

// in file: main.cpp

#include <iostream>
#include <stdexcept>
#include "vector.hpp"          // We use the Vector class
#include "SparseMatrix.hpp"    // We use the SparseMatrix class

int main() {
    std::cout << "--- Starting Part 6 Matrix-Vector Test ---" << std::endl;
    
    try {
        // 1. Define the Matrix A (A 3x3 simple matrix)
        // A = | 1 0 2 |
        //     | 0 3 0 |
        //     | 4 0 5 |
        // Rows=3, Cols=3, Capacity=5 (5 non-zero elements)
        SparseMatrix A(3, 3, 5); 

        // Add values to the matrix in order (CSR requires ordered insertion)
        A.setValue(0, 0, 1.0); // Row 0, Col 0, Value 1
        A.setValue(0, 2, 2.0); // Row 0, Col 2, Value 2
        A.setValue(1, 1, 3.0); // Row 1, Col 1, Value 3
        A.setValue(2, 0, 4.0); // Row 2, Col 0, Value 4
        A.setValue(2, 2, 5.0); // Row 2, Col 2, Value 5

        // 2. Define the Vector x
        // x = | 1.0 |
        //     | 2.0 |
        //     | 3.0 |
        std::vector<double> x_data = {1.0, 2.0, 3.0};
        Vector x(x_data); 

        // 3. Perform Multiplication (y = A * x)
        Vector y = A * x;

        // The expected result (y):
        // Row 0: (1*1 + 0*2 + 2*3) = 7.0
        // Row 1: (0*1 + 3*2 + 0*3) = 6.0
        // Row 2: (4*1 + 0*2 + 5*3) = 19.0
        
        // 4. Print Result
        std::cout << "Input Vector x: [" << x[0] << ", " << x[1] << ", " << x[2] << "]" << std::endl;
        std::cout << "Result Vector y: [" << y[0] << ", " << y[1] << ", " << y[2] << "]" << std::endl;
        
        // Final Check: Verify against expected values
        if (y[0] == 7.0 && y[1] == 6.0 && y[2] == 19.0) {
             std::cout << "TEST RESULT: SUCCESS! Matrix multiplication is correct." << std::endl;
        } else {
             std::cout << "TEST RESULT: FAILURE. Check Matrix::operator* logic." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}