/**
 * @file      gpio_input_output.c
 * @author    Fatih Kaan GÖKTÜRK
 * @brief     Bare-metal GPIO driver to read an input pin and toggle an LED.
 * 
 * @details   This program configures PA0 as a digital input to read physical 
 *            voltage states (HIGH/LOW) and PA5 as a digital output to drive 
 *            the onboard green LED of the STM32F446RE Nucleo board. It operates 
 *            entirely via direct memory-mapped register manipulation (RCC, MODER, 
 *            ODR, and IDR) without utilizing external HAL libraries.
 */

#include <stdint.h>

/** 
 * @brief RCC AHB1 Peripheral Clock Enable Register 
 *        Used to enable the clock for GPIO Port A.
 */
#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830U)

/** 
 * @brief GPIOA Port Mode Register 
 *        Used to configure the I/O direction mode (Input/Output/Analog/Alternate) of Port A pins.
 */
#define GPIOA_MODER (*(volatile uint32_t *)0x40020000U)

/** 
 * @brief GPIOA Output Data Register 
 *        Used to write digital HIGH (1) or LOW (0) states to Port A output pins.
 */
#define GPIOA_ODR   (*(volatile uint32_t *)0x40020014U)

/** 
 * @brief GPIOA Input Data Register 
 *        Used to read the physical digital voltage states (HIGH/LOW) of Port A pins.
 */
#define GPIOA_IDR   (*(volatile uint32_t *)0x40020010U)

/**
 * @brief  Main program loop.
 * @retval int Standard C return type, though embedded main() loops should never exit.
 */
int main(void) {
    
    /* 1. Enable clock for GPIO Port A */
    RCC_AHB1ENR |= (1U << 0);
    
    /* 2. Configure PA5 (LED) as General Purpose Output (Mode '01') */
    GPIOA_MODER &= ~((1U << 10) | (1U << 11)); // Clear bits 10 and 11
    GPIOA_MODER |= (1U << 10);                 // Set bit 10
    
    /* 3. Configure PA0 (Wire/Button) as Input (Mode '00') */
    GPIOA_MODER &= ~((1U << 0) | (1U << 1));   // Clear bits 0 and 1
    
    /* 4. Infinite Polling Loop */
    while(1) {
        
        // Read the physical state of PA0 by masking Bit 0 of the Input Data Register
        if (GPIOA_IDR & (1U << 0)) {
            // PA0 is HIGH (3.3V detected): Turn ON the LED
            GPIOA_ODR |= (1U << 5);
        } else {
            // PA0 is LOW (Ground detected): Turn OFF the LED safely
            GPIOA_ODR &= ~(1U << 5);
        }
        
    }
}