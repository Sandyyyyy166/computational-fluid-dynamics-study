# computational-fluid-dynamics-study

### 10.4 Update
A strong curiosity about Computational Fluid Dynamics (CFD) inspires me to start this journey. After self-studying C++ fundamentals for a while, I am undertaking this project to apply theoretical knowledge to a practical challenge, aiming to gain a deep understanding of the underlying data structures, numerical algorithms, and modern C++ software engineering practices involved in CFD solvers.
This repository will serve as my learning log, systematically showcasing the whole discovery process. I am following a tutorial called 'How to compile, write and use CFD libraries in C++' from cfd.university 

---

## Part 1: C++ Compilation and the Role of Libraries

C++ operates differently from an interpreted language like Python. 

**Compiler vs. Interpreter:** The core difference is WHEN the translation to machine code happens. A **Compiler** (like in C++) acts as a master translator, converting the entire source code into a fast, standalone executable file BEFORE you run it. In contrast, an **Interpreter** (like in Python) acts as a simultaneous translator, reading and executing the code line-by-line DURING runtime.

C++ requires a compilation step because the human-readable source code must be translated by a compiler into low-level machine code instructions that the CPU can execute directly. While this adds a step to the development process, it is precisely this translation that gives C++ its immense performance advantage at runtime, which is critical for scientific computing.

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
## Part 2 Discretising the Model Equation - From Physics to a Solvable Problem

The next thing that would be essential for this project is understanding the numerical method behind this physical model. 

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

---
## Part 3: Basic Library Structure

### 10.7 Update
My understanding from this chapter is that a robust C++ library requires a well-defined directory structure to enforce a separation of concerns. By placing the public interface (declarations in header files) into an `include/` directory and the private implementation (definitions in source files) into a `src/` directory, the library becomes far more organised and easier for an external application to use without exposing its internal workings.

### 10.9 Update
My work in this part involved creating several key components that separate the different concerns of the project:

1.  **The Library (Similar to The "Toolbox"):** This is the core of the project, containing the reusable code.
    * **`include/` directory:** This holds the public "interface" or "header" files (`.hpp`). It declares WHAT the library can do, serving as the menu for the user.
    * **`src/` directory:** This holds the private "implementation" files (`.cpp`). It defines HOW the library performs its functions, containing the actual logic.

2.  **The Application (Similar to The "User"):**
    * **`main.cpp`:** This is a standalone program that acts as a user or client of the library. Its purpose is to `#include` the library's public headers and CALL its functions to achieve a specific goal. It provides a clear example of HOW TO USE the library.

3.  **The Build System (Similar to The "Instructions"):**
    * **`Makefile`:** This is the instruction manual for the compiler. It defines all the necessary steps to compile the library's source files and the application's source files, and then **link** them together correctly to create a final, working executable program. It is the key to managing the relationship between all the different code files.

The fundamental difference is between the **library** (the general-purpose tool) and the **`main.cpp` application** (a specific use-case of that tool). This separation is the foundation of modular and scalable software design.

#### C++ Build and Execution Steps
Then it is important to learn how the running process works

**Step 1: Writing Code**
This is the manual step where I write the logic, like designing the blueprint.
-   **`include/cfd.hpp`:** The public blueprint, showing what the engine's connection points are.
-   **`src/cfd.cpp`:** The detailed, secret blueprint for how the engine is built internally.
-   **`main.cpp`:** The blueprint for the car's chassis and body, which shows where the engine needs to be installed.

**Step 2: Preprocessing**
* Before the main translation, a "preprocessor" runs. When it sees an `#include "cfd.hpp"` directive, it literally makes a copy of the contents of `cfd.hpp` and pastes it into the top of the `.cpp` file. This ensures each blueprint has all the information it needs.

**Step 3: Compilation**
* The compiler takes each `.cpp` file and translates it from C++ into the computer's native machine code. This step is like building the car parts in separate workshops.
* The compiler reads `main.cpp` and produces **`main.o`** (the finished car chassis).
* The compiler reads `src/cfd.cpp` and produces **`cfd.o`** (the finished engine).
* These `.o` files are called **object files**. They are self-contained, compiled components, but they are not yet a complete program. The chassis (`main.o`) knows it *needs* an engine, but it doesn't know where the engine (`cfd.o`) is yet.

**Step 4: Linking**
* The **Linker** is the final stage. Its job is to take all the finished components and connect them.
* It takes `main.o` (the chassis) and `cfd.o` (the engine).
* It resolves all the connections. It sees that `main.o` wants to call the `helloWorld` function and connects it to the actual `helloWorld` code living inside `cfd.o`.
* It bundles everything into a single, final file: the executable program named **`main`** (or `main.exe` on Windows). This is the finished, drivable car.

**Step 5: Execution**
* This is the final step where you, the user, run the program (`./main`). The operating system loads the executable file into memory and tells the processor to start carrying out the machine code instructions, starting from the `main` function.

### 10.20 Update (stopped a few days due to multiple courseworks deadlines)
To translate the theory from Part 3 into a tangible result, I set up the complete project foundation from scratch. This entire process was managed through the Terminal on my local machine to simulate a professional development environment.
The workflow involved several key steps:

1.  Scaffolding: I created the core directory structure (`src/` and `include/`) and all necessary empty files using command-line tools (`mkdir`, `touch`).
2.  Implementation: I chose "hello world" as the initial version of the library. The `hello_cfd` function served as a proof of concept to validate the project's structure.
3.  Building: The core task was writing a `Makefile` that could correctly compile the separate source files (`main.cpp`, `cfd.cpp`) into object files and then link them into a single, working executable.
4.  Publishing: After verifying locally that the program ran as expected, I initialized a Git repository, linked it to a new remote on GitHub, resolved initial configuration issues, and performed the first successful `git push` to publish the foundational code.

---
## Part 5: The Vector Class - Theoretical Deep Dive

### 10.21 Update
This chapter marks the beginning of building the core components for our solver. The first essential tool is a `Vector` class to handle the mathematical vectors in our `Ax=b` system. My study of this part focused on the key principles of C++ class design.

1. Why Create a Custom `Vector` Class?
While C++ has a powerful built-in `std::vector`, the goal here is to create a class specifically for mathematical vector operations. This means our class will have a fixed size upon creation and will support linear algebra operations like vector addition, subtraction, and dot products, which `std::vector` does not provide out of the box. For simplicity and robust memory management, our custom `Vector` class will use an `std::vector<double>` internally to store its data.

2. Core Components of a Well-Designed Class

My understanding of building this class involves several key C++ concepts:

* **Constructors** (The "Birth" of an object):
    * **`Vector(size_t size)`:** The primary constructor. It creates a vector of a specific `size`, initializing all its elements to zero. This is crucial for creating the `x` and `b` vectors in our `Ax=b` equation.
    * **`Vector(const std::vector<double>& data)`:** A convenience constructor to create our `Vector` from an existing list of numbers, which is useful for testing.

* **The Rule of Three/Five (Managing Copies):** This is a critical concept in C++ for managing memory correctly when objects are copied.
    * **Destructor `~Vector()`:** Cleans up when an object is destroyed. Since we are using `std::vector` internally, which handles its own memory, our destructor can be simple, but it's a required part of the rule.
    * **Copy Constructor `Vector(const Vector& other)`:** Defines what happens when we create a *new* vector by copying an existing one (e.g., `Vector v2 = v1;`). It must create a deep copy of the internal data.
    * **Copy Assignment Operator `operator=(const Vector& other)`:** Defines what happens when we assign an existing vector to another (e.g., `v2 = v1;`). The tutorial introduces the elegant copy-and-swap idiom here. This is a robust way to provide a strong exception safety guarantee and avoid code duplication. It works by creating a temporary copy and then swapping the internal data with the temporary object.
 
* **Operator Overloading (Making the Class Intuitive):**
    * This is the most powerful feature for our scientific computing class. It allows us to define how standard mathematical symbols (`+`, `-`, `*`) work with our `Vector` objects.
    * For example, by overloading `operator+`, we can write `Vector v3 = v1 + v2;` just like in mathematics, which is much more readable than `Vector v3 = v1.add(v2);`.
    * The plan is to overload operators for vector addition (`+`), subtraction (`-`), and scalar multiplication (`*`).

* **Essential Public Methods (The "API"):**
    * **`operator[](size_t index)`:** Allows accessing vector elements using familiar square bracket notation, like `v[i]`.
    * **`size()`:** A method to get the number of elements in the vector.

This theoretical groundwork provides a clear blueprint for the implementation. The focus is on creating a class that is not only functional but also robust, safe, and intuitive to use for mathematical programming.

### 10.24 Update
A Reflection on the First Major Push: Debugging the Git Workflow

When processing the initial implementation of the project's structure (Part 3) and the `Vector` class interface (Part 5), I encountered a significant series of challenges during the push to GitHub. This was a valuable, real-world lesson in debugging the development *process* itself, not just the code.

Here is a summary of the problems I faced and how I solved them:

1.  **The Initial Problem:** My `git push` was `[rejected]`. The error `(fetch first)` indicated that the remote GitHub repository had commits that my local machine did not have. This was likely due to the automatic creation of a file (like `.gitignore`) when I first set up the repository on the GitHub website.
2.  **The Complication:** The standard solution, `git pull`, repeatedly failed. The error `You have unstaged changes` blocked any attempt to pull or rebase.

3.  **The Root Cause (A Deeper Issue):** The "unstaged changes" were not simple; they were caused by a **filename case-sensitivity conflict**. My local macOS file system is **case-insensitive** (treating `README.md` and `readme.md` as the same file), while GitHub and Git are **case-sensitive** (treating them as two different files). This created a confusing state where Git couldn't tell what was staged, unstaged, or committed, leading to a loop where `git commit` and `git pull` would both fail.

