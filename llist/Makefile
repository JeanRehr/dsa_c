# Variables
CC = gcc
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj

# Debug flags (for debugging with gdb)
CFLAGS_DEBUG = -Iinclude -Wall -Wextra -pedantic -Werror -ggdb3 -fno-inline
LDFLAGS_DEBUG =

# Sanitizer flags (for testing, not debugging with gdb)
CFLAGS_SANITIZE = -Iinclude -Wall -Wextra -pedantic -Werror -fsanitize=address -fsanitize=undefined -fsanitize=leak -g
LDFLAGS_SANITIZE =

# Release flags
CFLAGS_RELEASE = -Iinclude -Wall -Wextra -O3 -DNDEBUG -fstack-protector-strong -fPIE -flto
LDFLAGS_RELEASE = -s -pie -flto

# Common libraries
COMMON_LIBS =

# Libraries for the main application
LDFLAGS_APP = $(COMMON_LIBS)

# Libraries for the test executable
LDFLAGS_TEST = $(COMMON_LIBS)

# Automatically find all .c files in the src and tests directories
SRCS = $(wildcard $(SRC_DIR)/*.c)
TESTS = $(wildcard $(TEST_DIR)/*.c)

# Binary targets
TARGET_APP = app.out
TARGET_TEST = tests.out

# Source files for each target
SRC_APP = $(SRCS)  # Include all source files for the main application
SRC_TEST = $(filter-out $(SRC_DIR)/main.c, $(SRCS)) $(TESTS)  # Exclude main.c for tests

# Object files for each target
OBJ_APP = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_APP))
OBJ_TEST = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter-out $(SRC_DIR)/main.c, $(SRCS))) \
           $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TESTS))

# Targets
.PHONY: all clean run_tests run_app debug sanitize release

# Default target (sanitize build)
all: sanitize

# Debug build
debug: CFLAGS = $(CFLAGS_DEBUG)
debug: LDFLAGS = $(LDFLAGS_DEBUG)
debug: $(TARGET_APP) $(TARGET_TEST)

# Sanitizer build
sanitize: CFLAGS = $(CFLAGS_SANITIZE)
sanitize: LDFLAGS = $(LDFLAGS_SANITIZE)
sanitize: $(TARGET_APP) $(TARGET_TEST)

# Release build
release: CFLAGS = $(CFLAGS_RELEASE)
release: LDFLAGS = $(LDFLAGS_RELEASE)
release: $(TARGET_APP) $(TARGET_TEST)

# Rule to build the main application
$(TARGET_APP): $(OBJ_APP)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDFLAGS_APP)

# Rule to build the test executable
$(TARGET_TEST): $(OBJ_TEST)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDFLAGS_TEST)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile test files into object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the test executable
run_tests: $(TARGET_TEST)
	./$(TARGET_TEST)

# Run the main application
run_app: $(TARGET_APP)
	./$(TARGET_APP)

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET_APP) $(TARGET_TEST)

#Variables:\
	CC: Specifies the compiler (gcc).\
	CFLAGS_DEBUG: Flags for debug builds (includes debugging symbols, strict warnings, and disables inlining for easier debugging with gdb).\
	CFLAGS_SANITIZE: Flags for sanitizer builds (includes sanitizers for memory errors, undefined behavior, and leaks, along with debugging symbols).\
	CFLAGS_RELEASE: Flags for release builds (includes optimizations, stack protection, position-independent code, and link-time optimization).\
	SRC_DIR: Directory containing source files (src/).\
	TEST_DIR: Directory containing test files (tests/).\
	OBJ_DIR: Directory for storing object files (obj/).\
	SRCS: Automatically finds all .c files in the src directory.\
	TESTS: Automatically finds all .c files in the tests directory.\
	TARGET_APP: Output executable for the main application (app.out).\
	TARGET_TEST: Output executable for the test suite (tests.out).\
	SRC_APP: Source files for the main application (includes all source files).\
	SRC_TEST: Source files for the test executable (excludes main.c and includes test files).\
	OBJ_APP: Object files for the main application.\
	OBJ_TEST: Object files for the test executable.\
	COMMON_LIBS: Linker flags common to both the main application and test executable.\
	LDFLAGS_APP: Linker flags for the main application (e.g., -lncurses for ncurses).\
	LDFLAGS_TEST: Linker flags for the test executable (e.g., -lcheck for the check unit testing framework).\
	LDFLAGS_DEBUG: Linker flags for debug builds (typically left empty unless additional linker options are needed).\
	LDFLAGS_SANITIZE: Linker flags for sanitizer builds (typically left empty unless additional linker options are needed).\
	LDFLAGS_RELEASE: Linker flags for release builds (includes stripping symbols and enabling position-independent executables).\
Targets:\
	all: Default target that builds both the application and test binaries in sanitizer mode.\
	debug: Builds both the application and test binaries in debug mode (optimized for debugging with gdb).\
	sanitize: Builds both the application and test binaries in sanitizer mode (enables memory and undefined behavior checks).\
	release: Builds both the application and test binaries in release mode (optimized for performance and stripped of debugging symbols).\
	run_tests: Executes the test executable.\
	run_app: Runs the main application.\
	clean: Removes generated object files and executables to clean up the directory.\
Usage:\
	With this setup in place, the following commands can be used:\
		make or make sanitize: Builds both the application and test binaries in sanitizer mode.\
		make debug: Builds both the application and test binaries in debug mode.\
		make release: Builds both the application and test binaries in release mode.\
		make run_app: Executes the main application, will execute the latest compiled version.\
		make run_tests: Runs the test suite, will execute the latest compiled version.\
		make clean: Cleans up the directory by removing built executables and object files.\