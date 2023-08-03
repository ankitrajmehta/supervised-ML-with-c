# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -g

# Source files and object files
SRCS := photo.c ml.c opener.c
OBJS := $(SRCS:.c=.o)
EXECUTABLE := run

# Main target (executable)
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE) -lm

# Rule to compile C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXECUTABLE)