# # Compiler settings
# CC := gcc
# CFLAGS := -Wall -Wextra -g

# # Source files and object files
# SRCS := photo.c ml.c opener.c
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


##make file for kisi

# CC = gcc
# CFLAGS = -Wall -Wextra -g
# FRAMEWORKS = -framework SDL2 -framework SDL2_ttf
# INCLUDE_DIRS = -I/home/ankit/Desktop/graphing/SDL2.framework/Headers -I/home/ankit/Desktop/graphing/SDL2_ttf.framework/Headers
# FRAMEWORK_DIRS = -F/Library/Frameworks

# SRC_FILES = opener.c photo.c ml.c
# OBJ_FILES = $(SRC_FILES:.c=.o)
# EXECUTABLE = run

# all: $(EXECUTABLE)

# $(EXECUTABLE): $(OBJ_FILES)
# 	$(CC) $(FRAMEWORKS) $(FRAMEWORK_DIRS) $(OBJ_FILES) -o $(EXECUTABLE)

# %.o: %.c
# 	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# clean:
# 	rm -f $(OBJ_FILES) $(EXECUTABLE)



CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lSDL2_ttf -lSDL2 -lm
INCLUDE_DIRS = -I/home/ankit/Desktop/graphing/SDL2.framework/Headers -I/home/ankit/Desktop/graphing/SDL2_ttf.framework/Headers
LIB_DIRS = -L/home/ankit/Desktop/graphing/SDL2.framework -L/home/ankit/Desktop/graphing/SDL2_ttf.framework

SRC_FILES =  main.c ml.c
OBJ_FILES = $(SRC_FILES:.c=.o)
EXECUTABLE = run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBS) $(LIB_DIRS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)
