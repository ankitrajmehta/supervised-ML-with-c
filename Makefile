# # Compiler settings
# CC := gcc
# CFLAGS := -Wall -Wextra -g

# # Source files and object files
# SRCS := ml.c main.c
# OBJS := $(SRCS:.c=.o)
# EXECUTABLE := run

# # Main target (executable)
# $(EXECUTABLE): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE) -lm

# # Rule to compile C files into object files
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Clean rule to remove object files and the executable
# clean:
# 	rm -f $(OBJS) $(EXECUTABLE)


CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lraylib -lm -lGL -lpthread -ldl -lrt -lX11

all: graph_program

graph_program: ra.o main.o
	$(CC) $(CFLAGS) -o run ra.o main.o $(LIBS)

ra.o: ra.c
	$(CC) $(CFLAGS) -c ra.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f graph_program ra.o main.o
