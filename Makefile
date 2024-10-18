# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source files
SRC = brent.c test.c

# Header files
HEADERS = brent.h

# Output executable
TARGET = test_program

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

# Clean rule to remove compiled files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
