# Core Concepts: Pointers in Embedded C

## 1. What is a Pointer?

A pointer is a variable that stores a memory address. In embedded systems we care deeply about *which* address and *what* lives there (RAM, flash, peripheral registers).

```c
uint32_t x = 10;
uint32_t *p = &x;   // p holds the address of x
*p = 20;            // write through the pointer
```

## 2. Why `volatile` is Non-Negotiable

Hardware registers and variables shared with Interrupt Service Routines (ISRs) can change at any moment. The compiler must not cache their values in registers.

```c
volatile uint32_t *reg = (volatile uint32_t *)0x40021000;
while ((*reg & 0x01) == 0) {  // re-reads every iteration
    // wait
}
```

## 3. Structure Overlay — The Preferred Style

Instead of calculating offsets manually, overlay a C structure on the peripheral base address:

```c
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t SR;
    volatile uint32_t DR;
} USART_TypeDef;

#define USART1  ((USART_TypeDef *)0x40011000UL)

USART1->CR |= (1 << 13);  // enable USART
```

This is safer, more readable, and less error-prone.

## 4. Pointer Arithmetic Rules

- `p + 1` advances by `sizeof(*p)` bytes
- Useful for buffers, DMA descriptors, and protocol parsing
- Be careful with alignment requirements of the target architecture

## 5. Function Pointers for Modular Design

```c
typedef void (*isr_handler_t)(void);

void uart_rx_handler(void) { /* ... */ }

isr_handler_t handlers[16] = {0};
handlers[USART1_IRQn] = uart_rx_handler;
```

## 6. Common Pitfalls

| Pitfall                  | Consequence                      | Mitigation                     |
|--------------------------|----------------------------------|--------------------------------|
| Missing `volatile`       | Infinite loops / wrong values    | Always mark hardware access    |
| Unaligned access         | Hard fault on some cores         | Use proper types / packing     |
| Dangling pointers        | Crashes / data corruption        | Null-check, lifetime discipline|
| Casting away `const`     | Undefined behavior               | Respect const correctness      |
| Null dereference         | Immediate crash                  | Always check before use        |

## 7. Recommended Practices

1. Prefer structure overlays over raw pointer + offset math.
2. Use `const` liberally to document intent.
3. Keep ISR code minimal; set flags or use queues that main loop processes.
4. Document every magic address with a comment or macro from the datasheet.
5. Enable compiler warnings (`-Wall -Wextra -Wpedantic`) and treat them seriously.
