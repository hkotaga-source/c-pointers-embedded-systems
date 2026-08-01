# C Pointers for Embedded Systems

A practical guide and code examples demonstrating the use of pointers in C, specifically tailored for embedded systems development.

## Why Pointers Matter in Embedded Systems

In embedded programming, pointers are essential for:

- **Direct memory access** — Reading and writing hardware registers
- **Memory-mapped I/O (MMIO)** — Controlling peripherals via address spaces
- **Efficient data structures** — Linked lists, buffers, circular queues without dynamic allocation overhead
- **DMA and buffer management** — Handling data transfers efficiently
- **Function pointers** — Implementing state machines, callbacks, and ISRs

## Project Structure

```
.
├── README.md
├── src/
│   ├── 01_pointer_basics.c
│   ├── 02_memory_mapped_io.c
│   ├── 03_pointer_arithmetic.c
│   ├── 04_function_pointers.c
│   └── 05_volatile_and_const.c
├── examples/
│   └── register_access_demo.c
└── docs/
    └── concepts.md
```

## Getting Started

These examples are written in standard C (C99+) and can be compiled with any compliant compiler (gcc, clang, arm-none-eabi-gcc, etc.).

```bash
# Compile a single example
gcc -Wall -Wextra -std=c99 src/01_pointer_basics.c -o pointer_basics

# Or use the provided Makefile (coming soon)
make
```

## Topics Covered

1. Pointer declaration, initialization, and dereferencing
2. Pointers to hardware registers (volatile)
3. Pointer arithmetic for buffers and arrays
4. Function pointers for modular embedded code
5. const correctness and safety in embedded contexts
6. Common pitfalls (null pointers, dangling pointers, alignment)

## Target Audience

- Embedded systems students and beginners
- Developers transitioning from higher-level languages to bare-metal C
- Anyone wanting solid foundations in low-level memory manipulation

## License

MIT License — feel free to use, modify, and share.
