//int main() {
    // We call the function from the library
    //hello_cfd();
    //return 0;
//}

// in file: main.cpp

#include <iostream>
// #include <stdexcept>
// #include <cmath>
// #include "vector.hpp"          // We use the SparseMatrix class
// #include "SparseMatrix.hpp"    // We use the Vector class
// #include "cfd.hpp"             // Now we use the solver function
#include "linearAlgebraLib.hpp" // Part 7: Replace all include by the static lib

/*//int main() {
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
}*/

int main() {
    std::cout << "--- Starting Part 4 Conjugate Gradient Solver Test ---" << std::endl;
    
    try {
        // 1. Define the System A x = b
        
        // Simple 3x3 SPD Matrix A (Non-zero capacity = 7)
        // A = | 2 -1 0 |
        //     |-1  2 -1|
        //     | 0 -1  2|
        SparseMatrix A(3, 3, 7); 
        A.setValue(0, 0, 2.0); A.setValue(0, 1, -1.0); 
        A.setValue(1, 0, -1.0); A.setValue(1, 1, 2.0); A.setValue(1, 2, -1.0);
        A.setValue(2, 1, -1.0); A.setValue(2, 2, 2.0); 

        // Right-hand side vector b
        // b = | 1.0 |
        //     | 0.0 |
        //     | 1.0 |
        Vector b({1.0, 0.0, 1.0});

        // Initial guess x0 (The exact solution is x = | 1, 1, 1 |)
        Vector x0({0.0, 0.0, 0.0}); 
        
        // Solver parameters
        size_t max_iterations = 100; 
        double tolerance = 1e-6; 

        // 2. Solve the system
        Vector x_solution = solve_cg(A, b, x0, max_iterations, tolerance);

        // 3. Print Final Result
        std::cout << "\nCG SOLVER TEST RESULT:" << std::endl;
        std::cout << "Expected Solution: [1.0, 1.0, 1.0]" << std::endl;
        std::cout << "Calculated Solution: ";
        for (size_t i = 0; i < x_solution.size(); ++i) {
            std::cout << x_solution[i] << (i < x_solution.size() - 1 ? ", " : "");
        }
        std::cout << "]" << std::endl;

        // Check the error
        Vector error = x_solution - Vector({1.0, 1.0, 1.0});
        double final_error = norm(error);
        
        if (final_error < 1e-5) {
             std::cout << "\nTEST RESULT: SUCCESS! CG Solver found the solution." << std::endl;
        } else {
             std::cout << "\nTEST RESULT: FAILURE. Final error too large." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}



