# --- Compiler and Flags ---
# Define the compiler to use
CC = g++
# Define compiler flags. -Iinclude tells the compiler where to find our header files.
CFLAGS = -std=c++11 -Iinclude
LIB_NAME = libLinearAlgebra.a

# --- Target: Main Executable ---
# Links the test program with the static library
main: main.o $(LIB_NAME)
	$(CC) main.o -L. -lLinearAlgebra -o main

# --- Target: Static Library ---
# Uses 'ar' to bundle object files into a library
$(LIB_NAME): vector.o SparseMatrix.o cfd.o
	ar rcs $(LIB_NAME) vector.o SparseMatrix.o cfd.o
	@echo "Static library $(LIB_NAME) created successfully!"

# --- Compilation Rules ---
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

vector.o: src/vector.cpp
	$(CC) $(CFLAGS) -c src/vector.cpp -o vector.o

SparseMatrix.o: src/SparseMatrix.cpp
	$(CC) $(CFLAGS) -c src/SparseMatrix.cpp -o SparseMatrix.o

cfd.o: src/cfd.cpp
	$(CC) $(CFLAGS) -c src/cfd.cpp -o cfd.o

# --- Utility: Clean ---
clean:
	rm -f *.o main $(LIB_NAME) solution.txt