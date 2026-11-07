/**
 * @file led_blink_baremetal.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-07
 * @brief Bare-metal register-level GPIO driver to turn on onboard LED (PA5) on STM32F446RE.
 *
 * This implementation accesses hardware memory-mapped registers directly using 
 * volatile pointer dereferencing without relying on vendor HAL/LL libraries.
 */

#include <stdint.h>

/* ========================================================================== */
/*                      STM32F446RE Hardware Addresses                        */
/* ========================================================================== */

/** @brief Base address for RCC AHB1 peripheral clock enable register. */
#define RCC_AHB1ENR_ADDR    0x40023830U

/** @brief Base address for GPIOA port mode register. */
#define GPIOA_MODER_ADDR    0x40020000U

/** @brief Base address for GPIOA port output data register. */
#define GPIOA_ODR_ADDR      0x40020014U

/* ========================================================================== */
/*                       Peripheral Register Access Macros                    */
/* ========================================================================== */

/** @brief Volatile pointer dereference macro for RCC AHB1 enable register. */
#define RCC_AHB1ENR         (*(volatile uint32_t *)RCC_AHB1ENR_ADDR)

/** @brief Volatile pointer dereference macro for GPIOA mode configuration register. */
#define GPIOA_MODER         (*(volatile uint32_t *)GPIOA_MODER_ADDR)

/** @brief Volatile pointer dereference macro for GPIOA output data register. */
#define GPIOA_ODR           (*(volatile uint32_t *)GPIOA_ODR_ADDR)

/* ========================================================================== */
/*                             Bitfield Definitions                           */
/* ========================================================================== */

/** @brief Bit 0 enables GPIOA bus clock on AHB1 bus. */
#define RCC_GPIOA_EN        (1U << 0)

/** @brief Clear mask for Mode Register bits [11:10] controlling pin 5. */
#define GPIO_MODER5_MASK    ((1U << 10) | (1U << 11))

/** @brief Bit 10 set (01b) sets PA5 to General Purpose Output mode. */
#define GPIO_MODER5_OUTPUT  (1U << 10)

/** @brief Bit 5 controls output level of GPIOA Pin 5 (LD2 onboard LED). */
#define GPIO_ODR5_HIGH      (1U << 5)

/**
 * @brief Application entry point configuring PA5 and driving it high.
 * @return Does not return (infinite loop prevents undefined execution).
 */
int main(void) {
    /* Step 1: Enable the peripheral bus clock for GPIO Port A */
    RCC_AHB1ENR |= RCC_GPIOA_EN;

    /* Step 2: Configure Pin PA5 as General Purpose Output (Mode: 01)
     * Clear bitfield [11:10] first to prevent residual state hazards */
    GPIOA_MODER &= ~GPIO_MODER5_MASK;
    /* Set bit 10 to configure output mode */
    GPIOA_MODER |= GPIO_MODER5_OUTPUT;

    /* Step 3: Drive PA5 high to light up onboard user LED (LD2) */
    GPIOA_ODR |= GPIO_ODR5_HIGH;

    /* Trap CPU in an infinite loop to prevent instruction fetch overruns */
    while (1) {
    }
}