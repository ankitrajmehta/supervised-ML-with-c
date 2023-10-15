
##make file for photo editing

# CC = gcc
# CFLAGS = -Wall -Wextra -g
# FRAMEWORKS = -framework SDL2 -framework SDL2_ttf
# INCLUDE_DIRS = -I(address of SDL2_ttf.framework/Headers)
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



##makefile for housing data

CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lSDL2_ttf -lSDL2 -lm
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
