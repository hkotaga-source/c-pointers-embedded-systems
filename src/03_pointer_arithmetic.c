/**
 * 03_pointer_arithmetic.c
 *
 * Pointer arithmetic is heavily used in embedded systems for:
 * - Walking through buffers (RX/TX rings, ADC samples, etc.)
 * - Parsing protocol frames
 * - Implementing circular buffers without index variables
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define BUFFER_SIZE 8

int main(void)
{
    uint8_t buffer[BUFFER_SIZE] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
    uint8_t *p = buffer;          /* points to first element */

    printf("=== Walking a buffer with pointer arithmetic ===\n");
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        printf("buffer[%zu] = 0x%02X  (via *p = 0x%02X, p = %p)\n",
               i, buffer[i], *p, (void *)p);
        p++;                      /* advances by sizeof(uint8_t) */
    }

    /* Reset and demonstrate larger type */
    uint16_t words[4] = {0xABCD, 0x1234, 0x5678, 0x9ABC};
    uint16_t *wp = words;

    printf("\n=== Pointer arithmetic with uint16_t ===\n");
    printf("wp starts at %p\n", (void *)wp);
    wp += 2;                      /* advances by 2 * sizeof(uint16_t) = 4 bytes */
    printf("After wp += 2: %p, value = 0x%04X\n", (void *)wp, *wp);

    /* Difference between two pointers (useful for length calculation) */
    uint8_t *start = &buffer[0];
    uint8_t *end   = &buffer[BUFFER_SIZE];
    ptrdiff_t len  = end - start;

    printf("\n=== Pointer difference ===\n");
    printf("end - start = %td elements\n", len);

    /*
     * Common embedded pattern: process a received frame
     * without copying data.
     */
    printf("\n=== Simulated frame processing ===\n");
    uint8_t frame[] = {0xAA, 0x05, 0x01, 0x02, 0x03, 0x04, 0x05, 0x55}; /* header, len, data..., footer */
    uint8_t *frame_ptr = frame;

    uint8_t header = *frame_ptr++;
    uint8_t length = *frame_ptr++;

    printf("Header: 0x%02X, Length: %u\n", header, length);
    printf("Payload: ");
    for (uint8_t i = 0; i < length; i++) {
        printf("0x%02X ", *frame_ptr++);
    }
    printf("\nFooter: 0x%02X\n", *frame_ptr);

    return 0;
}
