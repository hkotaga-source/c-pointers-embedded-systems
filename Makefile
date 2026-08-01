# Simple Makefile for the C Pointers Embedded Systems examples
# Works with host gcc. For cross-compilation replace CC with your toolchain.

CC       = gcc
CFLAGS   = -Wall -Wextra -Wpedantic -std=c99 -O0 -g
SRC_DIR  = src
BUILD_DIR = build

SOURCES  = $(wildcard $(SRC_DIR)/*.c)
TARGETS  = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SOURCES))

.PHONY: all clean run-basics help

all: $(BUILD_DIR) $(TARGETS)
	@echo "All examples built successfully."

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

# Quick demo targets
run-basics: $(BUILD_DIR)/01_pointer_basics
	./$(BUILD_DIR)/01_pointer_basics

run-mmio: $(BUILD_DIR)/02_memory_mapped_io
	./$(BUILD_DIR)/02_memory_mapped_io

run-arith: $(BUILD_DIR)/03_pointer_arithmetic
	./$(BUILD_DIR)/03_pointer_arithmetic

run-func: $(BUILD_DIR)/04_function_pointers
	./$(BUILD_DIR)/04_function_pointers

run-vol: $(BUILD_DIR)/05_volatile_and_const
	./$(BUILD_DIR)/05_volatile_and_const

help:
	@echo "Available targets:"
	@echo "  all          - Build every example"
	@echo "  clean        - Remove build artifacts"
	@echo "  run-basics   - Run pointer basics demo"
	@echo "  run-mmio     - Run memory-mapped I/O demo"
	@echo "  run-arith    - Run pointer arithmetic demo"
	@echo "  run-func     - Run function pointers demo"
	@echo "  run-vol      - Run volatile/const demo"
