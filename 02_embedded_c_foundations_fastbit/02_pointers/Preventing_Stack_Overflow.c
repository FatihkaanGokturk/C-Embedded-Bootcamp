/**
 * @file Preventing_Stack_Overflow.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-04
 * @brief Demonstrate struct passing by pointer to optimize memory and prevent stack overhead.
 */
#include <stdint.h>

// Imagine this struct contains bytes of complicated settings.
typedef struct {
    uint32_t baud_rate;
    uint8_t parity;
    // .. imagine 90 more bytes of data here 
} UART_Config_t;

// BAD way: Passes the struct by value, forcing the CPU to copy all bytes onto the stack
void Bad_init(UART_Config_t config_copy) {}

// GOOD way: Passes the struct by pointer, sending only the memory address
void Good_init(UART_Config_t *config_pointer) {
    if (config_pointer->baud_rate == 115200) {
        // Do something 
    }
}

int main(void) {
    UART_Config_t my_settings = {115200, 0};
    
    // We use & because we don't want to copy data, just pass its address
    Good_init(&my_settings);
    
    return 0;
}