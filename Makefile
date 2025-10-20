# Define the compiler to use
CC = g++
# Define compiler flags. -Iinclude tells the compiler where to find our header files.
CFLAGS = -std=c++11 -Iinclude

# --- Build Rules ---

# The final goal is an executable named "main"
# It depends on two compiled parts: main.o and cfd.o
main: main.o cfd.o
	$(CC) main.o cfd.o -o main

# Rule on how to create main.o from main.cpp
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

# Rule on how to create cfd.o from src/cfd.cpp
cfd.o: src/cfd.cpp
	$(CC) $(CFLAGS) -c src/cfd.cpp

# A helpful rule to clean up all generated files
clean:
	rm -f *.o main