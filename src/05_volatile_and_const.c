/**
 * 05_volatile_and_const.c
 *
 * Critical qualifiers when using pointers in embedded systems:
 *
 * - volatile  : Prevents compiler optimizations that assume memory doesn't change
 *               (required for hardware registers, shared variables with ISRs)
 * - const     : Promises the pointed-to data will not be modified through this pointer
 * - const + volatile combinations for read-only hardware registers
 */

#include <stdio.h>
#include <stdint.h>

/* Simulated hardware register that can change outside the program */
volatile uint32_t * const HW_STATUS_REG = (volatile uint32_t *)0x40000000UL;

/* Read-only status register (const volatile) */
const volatile uint32_t * const HW_RO_STATUS = (const volatile uint32_t *)0x40000004UL;

void example_volatile(void)
{
    /*
     * Without volatile, a compiler might optimize this loop away
     * if it thinks the value never changes.
     */
    printf("Waiting for hardware ready flag (simulated)...\n");

    /* In real code you would poll a real register */
    volatile uint32_t flag = 0;
    /* while (flag == 0) { }  <-- this is why volatile matters */

    printf("Volatile ensures the compiler re-reads memory every time.\n");
}

void example_const(void)
{
    uint32_t data = 42;
    const uint32_t *p_const = &data;   /* cannot modify *p_const */
    uint32_t * const p_fixed = &data;  /* cannot change the pointer itself */

    /* *p_const = 100;  // COMPILE ERROR */
    /* p_fixed = NULL;  // COMPILE ERROR */

    printf("const correctness helps catch bugs at compile time.\n");
    printf("Value via const pointer: %u\n", *p_const);
}

int main(void)
{
    example_volatile();
    example_const();

    printf("\nKey takeaways:\n");
    printf("  - Use volatile for any memory that can change unexpectedly\n");
    printf("  - Use const to express intent and enable compiler checks\n");
    printf("  - Combine them for read-only hardware registers\n");

    return 0;
}
