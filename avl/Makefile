# Variables
CC = gcc
# Really display all warnings and be pedatic, make all warnings errors, tell if there is a mem leak
CFLAGS = -Iinclude -Wall -Wextra -pedantic -Werror -fsanitize=address
VPATH = src include

# Binary targets
TARGET_APP = app
TARGET_TEST = tests

# Source files
#SRC_APP = main.c avltree.c
SRC_APP = avltree.c
SRC_TEST = avltreetests.c avltree.c

# Targets
.PHONY: all clean run_tests run_app

all: $(TARGET_APP) $(TARGET_TEST)

$(TARGET_APP): $(SRC_APP)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_TEST): $(SRC_TEST)
	$(CC) $(CFLAGS) -o $@ $^

run_tests: $(TARGET_TEST)
	./$(TARGET_TEST)

run_app: $(TARGET_APP)
	./$(TARGET_APP)

clean:
	rm -f $(TARGET_APP) $(TARGET_TEST)

#Explanation\
Variables:\
	CC: Specifies the compiler (gcc).\
	CFLAGS: Includes flags for displaying all warnings and specifying include paths (include/).\
Targets:\
	all: Default target that builds both the application and tests.\
	$(TARGET_APP): Builds the driver code (main.c). Assumes output executable is app.\
	$(TARGET_TEST): Builds the test suite (avltreetests.c). Assumes output executable is tests.\
	run_tests: Executes tests.\
	run_app: Runs the application.\
	clean: Removes generated executables to clean up the directory.\
Using VPATH simplifies sourcing paths for files specified across subdirectories.\
Usage\
With this setup in place, you can use the following commands:\
	make or make all: Builds both the application and test binaries.\
	make run_app: Executes the driver application.\
	make run_tests: Runs unit tests.\
	make clean: Cleans up the directory by removing built executables.\