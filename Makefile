# Cross-platform Makefile for SM9 Library
# Supports: Linux, macOS, Windows (MinGW/MSYS2)

CC = gcc
CFLAGS += -Wall -O2 -I$(INCLUDE_DIR)
LDFLAGS += -lm

# Directories
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Detect operating system
ifeq ($(OS),Windows_NT)
    TARGET_OS = Windows
    RM = del /Q
    MKDIR = mkdir
    TARGET_EXT = .exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        TARGET_OS = Linux
    endif
    ifeq ($(UNAME_S),Darwin)
        TARGET_OS = macOS
    endif
    RM = rm -f
    MKDIR = mkdir -p
    TARGET_EXT =
endif

# Core sources
CORE_SRCS = $(SRC_DIR)/core/bigint.c \
            $(SRC_DIR)/core/field2.c \
            $(SRC_DIR)/core/field4.c \
            $(SRC_DIR)/core/field12.c

# Curve sources
CURVE_SRCS = $(SRC_DIR)/curve/point.c \
             $(SRC_DIR)/curve/point2.c \
             $(SRC_DIR)/curve/pairing.c

# Hash sources
HASH_SRCS = $(SRC_DIR)/hash/sm3.c \
            $(SRC_DIR)/hash/sm4.c

# SM9 sources
SM9_SRCS = $(SRC_DIR)/sm9/params.c \
           $(SRC_DIR)/sm9/sm9_dsa.c \
           $(SRC_DIR)/sm9/sm9_ka.c \
           $(SRC_DIR)/sm9/sm9_pkc.c

# Utility
UTILITY_SRCS = $(SRC_DIR)/utility.c

# All library sources
LIB_SRCS = $(CORE_SRCS) $(CURVE_SRCS) $(HASH_SRCS) $(SM9_SRCS) $(UTILITY_SRCS)

# Object files
LIB_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(LIB_SRCS))

# Test sources
TEST_SRCS = tests/test_sm9.c
TEST_OBJ = $(BUILD_DIR)/test_sm9.o

# Library and executable
LIBRARY = $(BUILD_DIR)/libsm9.a
BIN = $(BIN_DIR)/sm9_test$(TARGET_EXT)

# Create directories
$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)
	$(MKDIR) $(BUILD_DIR)/core
	$(MKDIR) $(BUILD_DIR)/curve
	$(MKDIR) $(BUILD_DIR)/hash
	$(MKDIR) $(BUILD_DIR)/sm9

$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)

# Compile source files
$(BUILD_DIR)/core/%.o: $(SRC_DIR)/core/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/curve/%.o: $(SRC_DIR)/curve/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/hash/%.o: $(SRC_DIR)/hash/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/sm9/%.o: $(SRC_DIR)/sm9/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library
$(LIBRARY): $(LIB_OBJS) | $(BUILD_DIR)
	ar rcs $@ $(LIB_OBJS)

# Build test executable
$(BIN): $(TEST_OBJ) $(LIBRARY) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $(TEST_OBJ) -L$(BUILD_DIR) -lsm9

all: $(BIN)

test: $(BIN)
	./$(BIN)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(BIN_DIR)
	$(RM) *.o
	$(RM) $(BIN)

.PHONY: all clean test
