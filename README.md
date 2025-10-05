# computational-fluid-dynamics-study

### 10.4 Update
A strong curiosity about Computational Fluid Dynamics (CFD) inspires me to start this journey. After self-studying C++ fundamentals for a while, I am undertaking this project to apply theoretical knowledge to a practical challenge, aiming to gain a deep understanding of the underlying data structures, numerical algorithms, and modern C++ software engineering practices involved in CFD solvers.
This repository will serve as my learning log, systematically showcasing the whole discovery process. I am following a tutorial called 'How to compile, write and use CFD libraries in C++' from cfd.university 

---

## Part 1: C++ Compilation and the Role of Libraries

C++ operates differently from an interpreted language like Python. C++ requires a compilation step because the human-readable source code must be translated by a compiler into low-level machine code instructions that the CPU can execute directly. While this adds a step to the development process, it is precisely this translation that gives C++ its immense performance advantage at runtime, which is critical for scientific computing.

A **library** is simply a collection of pre-written, reusable code (like functions or classes) designed to be used by another program, it **cannot contain its own `main()` function**. This is because `main()` is the unique starting point for a program's execution, and having two would create a conflict.

Therefore, before attempting to build my own, it's essential to first understand the common types of C++ libraries.

### 10.5 Update

#### Static Libraries
A **static library** is essentially an archive of code that is directly copied and linked into your application's final executable file during compilation.

My understanding is that it's best suited for smaller applications or environments where deployment simplicity is critical. Because the library code is part of the main program, you don't have to worry about missing library files on the user's machine, which avoids runtime errors. However, this convenience comes at the cost of a much larger executable file size.

#### Dynamic Libraries

A **dynamic library** is a collection of reusable code kept in a separate file that is loaded by the operating system only when your application is running (at runtime), rather than being bundled directly into the executable.

My understanding is that dynamic libraries are ideal for large-scale applications or modular systems where keeping the main program lightweight is important. Their biggest advantages are the small executable size and the ability to update the library without needing to recompile the entire application. This is also highly efficient when multiple programs on a system need to use the same shared functionality. The trade-off is the increased complexity of managing these dependencies at runtime and ensuring the correct library version is available on the user's system.

#### Header-only Libraries

A **header-only library** is a library where the entire code, including both the declarations and the implementations, is written directly inside the header files (`.h` or `.hpp`). There are no separate `.cpp` files to compile for the library itself; you simply use the `#include` directive to integrate it, and the compiler treats the library's code as if it were part of your own source file.

My understanding is that header-only libraries are the ultimate choice for convenience and ease of integration. They are perfect for distributing smaller utilities or libraries that are heavily based on C++ templates, as they completely eliminate the complexities of the linking process. However, this simplicity comes at a direct cost to compilation speed. Because the entire library is copied into every source file that includes it, the compiler has to do much more work, which can significantly slow down the build process for large projects.

#### A Note on `#include`: Angle Brackets `<>` vs. Double Quotes `""`

An important practical detail I learned is the difference in how files are included:

-   **`#include <library.h>`:** The **angle brackets** are used for **standard system libraries** (e.g., `<iostream>`, `<vector>`). This tells the compiler to search only in the default system-wide include directories where standard libraries are installed.

-   **`#include "library.h"`:** The **double quotes** are for **my own header files** or **third-party libraries** included within this project. This tells the compiler to search **first** in the current project directory, and only then to check the system directories if the file isn't found locally.

The convention I will follow is to use `<>` for standard libraries and `""` for all files that are a local part of this project.

---
## Part 2 Discretising the Model Equation

The next thing that would be essential for this project is understanding the numerical method behind this physical model. 

### Part 2: Discretising the Model Equation - From Physics to a Solvable Problem

This chapter forms the theoretical bedrock of the entire library, detailing the crucial process of translating a physical phenomenon into a format a computer can solve.

-   **The Physical Problem & Governing Equation:** The steady-state heat equation is a good example to study when developing a linear algebra library to solve the discretised equation **$Ax = b$**. This is governed by a Partial Differential Equation (PDE), specifically the Laplace Equation, $\nabla^2 T = 0$. I understand this equation as a "rule of smoothness," stating that the temperature at any point is the average of its immediate surroundings.

-   **The Computational Challenge:** A computer cannot operate on a continuous domain with infinite points. The core challenge is to translate this continuous PDE into a discrete system of algebraic equations. This translation process is known as **discretisation**.

-   **The Chosen Method (Finite Volume Method - FVM):** My key takeaway is that FVM's strength lies in its enforcement of conservation laws. It works by:
    1.  Dividing the continuous physical domain into a finite grid of small "control volumes" or "cells".
    2.  Applying the physical law (heat in = heat out) to each individual cell, rather than at a single point.
    3.  Approximating the heat "flux" between a cell and its neighbors based on their temperature differences.

-   **The Final Outcome (A Solvable System):** By applying the FVM rules to every cell in the grid, the complex PDE is systematically transformed into a large system of coupled linear equations. This system is elegantly represented in the matrix form **$Ax = b$**, where:
    -   `x` is the vector of unknown temperatures at the center of each cell—this is the solution we are seeking.
    -   `A` is a large, sparse matrix of coefficients that defines the relationship between each cell and its direct neighbors.
    -   `b` is a vector representing the knowns, such as heat sources or the fixed temperatures at the boundaries of the domain (**boundary conditions**).

My understanding is now clear: the primary purpose of the C++ code to be written in the following chapters is to build the data structures (`Vector`, `SparseMatrix`) and algorithms (`Solver`) necessary to construct and solve this very `Ax=b` system.
