# Define the compiler to use
CC = g++
# Define compiler flags. -Iinclude tells the compiler where to find our header files.
CFLAGS = -std=c++11 -Iinclude

# --- Build Rules ---

# The final goal is an executable named "main"
# It depends on two compiled parts: main.o and cfd.o
# Add vector.o and SparseMatrix.o to the dependency list and the linking command
main: main.o cfd.o vector.o SparseMatrix.o
	$(CC) main.o cfd.o vector.o SparseMatrix.o -o main

# Rule on how to create main.o from main.cpp
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

# Rule on how to create cfd.o from src/cfd.cpp
cfd.o: src/cfd.cpp
	$(CC) $(CFLAGS) -c src/cfd.cpp

# A helpful rule to clean up all generated files
clean:
	rm -f *.o main

vector.o: src/vector.cpp
	$(CC) $(CFLAGS) -c src/vector.cpp -o vector.o

# ... (main.o, cfd.o, vector.o rules are unchanged)

# --- Compilation Rule for SparseMatrix (NEW) ---
SparseMatrix.o: src/SparseMatrix.cpp
	$(CC) $(CFLAGS) -c src/SparseMatrix.cpp -o SparseMatrix.o

# ... (clean rule is unchanged)

# --- Compiler and Flags ---
CC = g++
CFLAGS = -std=c++11 -Iinclude
LIB_NAME = libLinearAlgebra.a

# --- Target: Main Executable ---
# Links the test program with the static library
main: main.o $(LIB_NAME)
	$(CC) main.o -L. -lLinearAlgebra -o main

# --- Target: Static Library ---
# Uses 'ar' (archiver) to bundle object files into a library
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
	rm -f *.o main $(LIB_NAME)
