/**
 * 02_memory_mapped_io.c
 *
 * Demonstrates how pointers are used to access memory-mapped hardware registers
 * in embedded systems. This is the core technique for controlling peripherals.
 *
 * Note: Addresses used here are illustrative (typical for many MCUs).
 * On real hardware you would use the exact base addresses from the datasheet.
 */

#include <stdint.h>
#include <stdio.h>

/* Simulated peripheral base addresses (example values) */
#define GPIOA_BASE      0x40020000UL
#define RCC_BASE        0x40023800UL

/* Register offsets */
#define GPIO_MODER_OFFSET   0x00
#define GPIO_ODR_OFFSET     0x14
#define RCC_AHB1ENR_OFFSET  0x30

/* Helper macro to create a volatile pointer to a register */
#define REG32(addr)     (*(volatile uint32_t *)(addr))

/* Cleaner way: structure overlay for a peripheral */
typedef struct {
    volatile uint32_t MODER;    /* 0x00 Mode register */
    volatile uint32_t OTYPER;   /* 0x04 Output type */
    volatile uint32_t OSPEEDR;  /* 0x08 Output speed */
    volatile uint32_t PUPDR;    /* 0x0C Pull-up/pull-down */
    volatile uint32_t IDR;      /* 0x10 Input data */
    volatile uint32_t ODR;      /* 0x14 Output data */
    /* ... more registers omitted for brevity */
} GPIO_TypeDef;

/* Cast the base address to a structure pointer */
#define GPIOA           ((GPIO_TypeDef *)GPIOA_BASE)

int main(void)
{
    /*
     * Method 1: Raw pointer arithmetic / macro access
     * This is common in many vendor HALs and low-level drivers.
     */
    printf("=== Method 1: Direct register access via macros ===\n");

    /* Enable GPIOA clock (example bit) */
    REG32(RCC_BASE + RCC_AHB1ENR_OFFSET) |= (1UL << 0);

    /* Configure PA5 as output (MODER5 = 01) */
    REG32(GPIOA_BASE + GPIO_MODER_OFFSET) &= ~(3UL << 10);  /* clear bits */
    REG32(GPIOA_BASE + GPIO_MODER_OFFSET) |=  (1UL << 10);  /* set to 01 */

    /* Toggle PA5 */
    REG32(GPIOA_BASE + GPIO_ODR_OFFSET) ^= (1UL << 5);

    printf("Simulated: GPIOA MODER and ODR registers updated.\n");

    /*
     * Method 2: Structure overlay (much cleaner and less error-prone)
     */
    printf("\n=== Method 2: Structure overlay ===\n");

    /* Same operations using the typed structure */
    GPIOA->MODER &= ~(3UL << 10);
    GPIOA->MODER |=  (1UL << 10);
    GPIOA->ODR   ^=  (1UL << 5);

    printf("Simulated: GPIOA accessed via structure pointer.\n");

    /*
     * Important notes for real embedded work:
     * - Always use 'volatile' for hardware registers
     * - Prefer structure overlays over raw offsets when possible
     * - Check datasheet for exact addresses and bit fields
     * - Consider using CMSIS or vendor headers for production code
     */

    return 0;
}
