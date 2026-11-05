/**
 * @file mock_gpio_register.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-05
 * @brief Emulate hardware register manipulation using a macro-wrapped volatile pointer.
 */

#include <stdio.h>
#include <stdint.h>

// Simulated 32-bit peripheral register in RAM
uint32_t fake_hardware_register = 0x00000000;

// Wrap variable address into a volatile hardware register pointer macro
#define MOCK_GPIO_ODR  ((volatile uint32_t *)&fake_hardware_register)

/**
 * @brief Sets bit 5 of the mock output data register (simulating GPIO pin high).
 */
void Set_LED_Pin(void) {
    // Bitwise OR to set bit 5 without modifying other bits
    *MOCK_GPIO_ODR |= (1UL << 5);
}

int main(void) {
    printf("Register before: 0x%08X\n", fake_hardware_register);
    
    Set_LED_Pin();
    
    // Bit 5 set: 0x00000020 (1 << 5)
    printf("Register after:  0x%08X\n", fake_hardware_register); 
    
    return 0;
}