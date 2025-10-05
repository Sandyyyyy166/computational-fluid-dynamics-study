# computational-fluid-dynamics-study

## 10.4 Update
A strong curiosity about Computational Fluid Dynamics (CFD) inspires me to start this journey. After self-studying C++ fundamentals for a while, I am undertaking this project to apply theoretical knowledge to a practical challenge, aiming to gain a deep understanding of the underlying data structures, numerical algorithms, and modern C++ software engineering practices involved in CFD solvers.
This repository will serve as my learning log, systematically showcasing the whole discovery process.

---

### Part 1: C++ Compilation and the Role of Libraries

C++ operates differently from an interpreted language like Python. C++ requires a compilation step because the human-readable source code must be translated by a compiler into low-level machine code instructions that the CPU can execute directly. While this adds a step to the development process, it is precisely this translation that gives C++ its immense performance advantage at runtime, which is critical for scientific computing.

A **library** is simply a collection of pre-written, reusable code (like functions or classes) designed to be used by another program, it **cannot contain its own `main()` function**. This is because `main()` is the unique starting point for a program's execution, and having two would create a conflict.

Therefore, before attempting to build my own, it's essential to first understand the common types of C++ libraries.

#### Static Libraries
A **static library** is essentially an archive of code that is directly copied and linked into your application's final executable file during compilation.

My understanding is that it's best suited for smaller applications or environments where deployment simplicity is critical. Because the library code is part of the main program, you don't have to worry about missing library files on the user's machine, which avoids runtime errors. However, this convenience comes at the cost of a much larger executable file size.

#### Dynamic Libraries

A **dynamic library** is a collection of reusable code kept in a separate file that is loaded by the operating system only when your application is running (at runtime), rather than being bundled directly into the executable.

My understanding is that dynamic libraries are ideal for large-scale applications or modular systems where keeping the main program lightweight is important. Their biggest advantages are the small executable size and the ability to update the library without needing to recompile the entire application. This is also highly efficient when multiple programs on a system need to use the same shared functionality. The trade-off is the increased complexity of managing these dependencies at runtime and ensuring the correct library version is available on the user's system.
