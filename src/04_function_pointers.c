/**
 * 04_function_pointers.c
 *
 * Function pointers are powerful in embedded systems for:
 * - State machines
 * - Callback registration (timers, UART RX, button presses)
 * - Jump tables / command handlers
 * - Lightweight polymorphism without C++
 */

#include <stdio.h>
#include <stdint.h>

/* Simple state machine example using function pointers */
typedef void (*state_handler_t)(void);

void state_idle(void);
void state_running(void);
void state_error(void);

/* Current state */
static state_handler_t current_state = state_idle;

void state_idle(void)
{
    printf("State: IDLE - waiting for start command\n");
    /* Simulate transition */
    current_state = state_running;
}

void state_running(void)
{
    printf("State: RUNNING - processing data\n");
    /* Simulate error condition */
    current_state = state_error;
}

void state_error(void)
{
    printf("State: ERROR - recovering...\n");
    current_state = state_idle;
}

/* Callback example (like a timer or ISR callback) */
typedef void (*callback_t)(uint32_t data);

void on_data_received(uint32_t data)
{
    printf("Callback: received data = 0x%08X\n", data);
}

void register_and_invoke(callback_t cb, uint32_t value)
{
    if (cb != NULL) {
        cb(value);
    }
}

int main(void)
{
    printf("=== Function pointer state machine ===\n");
    for (int i = 0; i < 4; i++) {
        current_state();          /* call the current state handler */
    }

    printf("\n=== Callback registration pattern ===\n");
    register_and_invoke(on_data_received, 0x12345678);
    register_and_invoke(NULL, 0); /* safe null check */

    /* Array of function pointers (jump table) */
    state_handler_t handlers[] = {state_idle, state_running, state_error};
    printf("\n=== Jump table ===\n");
    for (size_t i = 0; i < 3; i++) {
        handlers[i]();
    }

    return 0;
}
