# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Source files
SRCS = main.c lexer.c
OBJS = $(SRCS:.c=.o)

# Output binary
TARGET = sf

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program with a test file
run: $(TARGET)
	./$(TARGET) test.sf
