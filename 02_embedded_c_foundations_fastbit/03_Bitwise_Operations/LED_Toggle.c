/**
 * @file main.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-07
 * @brief Turn on onboard LED (PA5) on STM32F446RE via raw register pointer macros.
 */

#include <stdint.h>

// --- RAW HARDWARE ADDRESSES FROM STM32F446RE DATASHEET ---
#define RCC_AHB1ENR_ADDR   0x40023830U
#define GPIOA_MODER_ADDR   0x40020000U
#define GPIOA_ODR_ADDR     0x40020014U

// Type-cast raw addresses to volatile uint32_t pointers and dereference them
#define RCC_AHB1ENR (*(volatile uint32_t *)RCC_AHB1ENR_ADDR)
#define GPIOA_MODER (*(volatile uint32_t *)GPIOA_MODER_ADDR)
#define GPIOA_ODR   (*(volatile uint32_t *)GPIOA_ODR_ADDR)

int main(void) {
    // 1. Enable the clock for GPIOA (Set bit 0 of RCC_AHB1ENR)
    RCC_AHB1ENR |= (1U << 0);
    
    // 2. Configure PA5 as Output (Bits 11 and 10 in GPIOA_MODER)
    // Clear bits 10 and 11
    GPIOA_MODER &= ~((1U << 10) | (1U << 11));
    // Set bit 10 to select output mode (01)
    GPIOA_MODER |= (1U << 10);
    
    // 3. Turn on the LED (Set bit 5 of GPIOA_ODR)
    GPIOA_ODR |= (1U << 5);

    // Infinite loop prevents CPU from falling off main into garbage memory
    while (1) {
    }
}