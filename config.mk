PROJECT_NAME = king and pigs

# directories
BIN_DIR = bin
BINARY = binary
SRC_DIR = src
LOG_DIR = log
LIB_DIR = lib
TEST_DIR = test

# Source code file extension
SRCEXT = cpp

# Defines the Compiler
CC = g++

# Dependency libraries
LIBS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lbox2d
 
# Defines the language standards for GCC
# STD = -std=c11 

# Protection for stack-smashing attack
# STACK = -fstack-protector-all -Wstack-protector

# Specifies to GCC the required warnings
# WARNS = -Wall -Wextra -pedantic 

# Flags for compiling 
CFLAGS = -O3 $(STD) $(STACK) $(WARNS)

# Debug options
DEBUG = -g3 -DDEBUG=1
