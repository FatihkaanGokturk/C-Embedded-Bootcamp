#include <stdint.h>

/**
 * @brief  Industry-standard GPIO Peripheral Register Map
 * @note   The order of these variables MUST perfectly match the STM32 Reference Manual.
 *         Each uint32_t automatically steps the memory address forward by 0x04.
 */
typedef struct {
    volatile uint32_t MODER;    // Address Offset: 0x00
    volatile uint32_t OTYPER;   // Address Offset: 0x04
    volatile uint32_t OSPEEDR;  // Address Offset: 0x08
    volatile uint32_t PUPDR;    // Address Offset: 0x0C
    volatile uint32_t IDR;      // Address Offset: 0x10
    volatile uint32_t ODR;      // Address Offset: 0x14
} GPIO_TypeDef;

// --- HARDWARE BASE ADDRESSES ---
// We cast the raw base memory address of Port A into a pointer of our struct type.
#define GPIOA ((GPIO_TypeDef *)0x40020000U)
// If you ever wanted to use Port B, you just add its base address!
#define GPIOB ((GPIO_TypeDef *)0x40020400U)

#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830U)

int main(void) {
    // 1. Enable Clock for Port A
    RCC_AHB1ENR |= (1U << 0);
    
    // 2. Configure PA5 as Output (LED) using the struct pointer
    GPIOA->MODER &= ~((1U << 10) | (1U << 11)); 
    GPIOA->MODER |= (1U << 10);
    
    // 3. Configure PA0 as Input (Button/Wire)
    GPIOA->MODER &= ~((1U << 0) | (1U << 1));

    while(1) {
        // 4. Poll the Input Data Register via the struct
        if (GPIOA->IDR & (1U << 0)) {
            // Turn ON the LED
            GPIOA->ODR |= (1U << 5);
        } else {
            // Turn OFF the LED
            GPIOA->ODR &= ~(1U << 5);
        }
    }
}