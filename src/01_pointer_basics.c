/**
 * 01_pointer_basics.c
 *
 * Fundamental pointer concepts in C, demonstrated with an embedded mindset.
 * No dynamic allocation (malloc) is used — common practice in many embedded systems.
 */

#include <stdio.h>
#include <stdint.h>

int main(void)
{
    /* 1. Basic pointer declaration and initialization */
    uint32_t value = 0xDEADBEEF;
    uint32_t *ptr = &value;          /* ptr holds the address of value */

    printf("Value:            0x%08X\n", value);
    printf("Address of value: %p\n", (void *)&value);
    printf("Pointer value:    %p\n", (void *)ptr);
    printf("Dereferenced:     0x%08X\n", *ptr);

    /* 2. Modifying data through a pointer */
    *ptr = 0xCAFEBABE;
    printf("\nAfter *ptr = 0xCAFEBABE:\n");
    printf("value is now:     0x%08X\n", value);

    /* 3. Pointer to a pointer (double indirection) */
    uint32_t **pptr = &ptr;
    printf("\nDouble indirection:\n");
    printf("**pptr = 0x%08X\n", **pptr);

    /* 4. Null pointer safety pattern commonly used in embedded code */
    uint32_t *maybe_null = NULL;
    if (maybe_null != NULL) {
        *maybe_null = 42;            /* never reached */
    } else {
        printf("\nNull pointer check passed (good practice).\n");
    }

    /* 5. Size of pointers (architecture dependent) */
    printf("\nSize of pointer:  %zu bytes\n", sizeof(ptr));
    printf("Size of uint32_t: %zu bytes\n", sizeof(uint32_t));

    return 0;
}
