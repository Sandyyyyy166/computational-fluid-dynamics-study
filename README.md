# computational-fluid-dynamics-study

## 10.4 Update
A strong curiosity about Computational Fluid Dynamics (CFD) inspires me to start this journey. After self-studying C++ fundamentals for a while, I am undertaking this project to apply theoretical knowledge to a practical challenge, aiming to gain a deep understanding of the underlying data structures, numerical algorithms, and modern C++ software engineering practices involved in CFD solvers.
This repository will serve as my learning log, systematically showcasing the whole discovery process.

---

### Part 1: C++ Compilation and the Role of Libraries

C++ operates differently from an interpreted language like Python. C++ requires a compilation step because the human-readable source code must be translated by a compiler into low-level machine code instructions that the CPU can execute directly. While this adds a step to the development process, it is precisely this translation that gives C++ its immense performance advantage at runtime, which is critical for scientific computing.

A **library** is simply a collection of pre-written, reusable code (like functions or classes) designed to be used by another program, it **cannot contain its own `main()` function**. This is because `main()` is the unique starting point for a program's execution, and having two would create a conflict.

Therefore, before attempting to build my own, it's essential to first understand the common types of C++ libraries.
