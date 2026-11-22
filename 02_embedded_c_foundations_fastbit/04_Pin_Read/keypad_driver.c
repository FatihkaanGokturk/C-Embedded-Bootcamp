/**
 * @file      keypad_driver.c
 * @author    Fatih Kaan GÖKTÜRK
 * @brief     Bare-metal 4x4 matrix keypad scanner for STM32F446RE.
 *
 * @details   Maps Rows R1-R4 to PC0-PC3 (Outputs) and Columns C1-C4 to PC4-PC7
 *            (Inputs with internal Pull-Up resistors). Scans one active-LOW row
 *            at a time and debounces detected key presses.
 */

#include <stdint.h>

/**
 * @brief Industry-standard GPIO Peripheral Register Map (RM0390)
 */
typedef struct {
    volatile uint32_t MODER;    // Offset 0x00: Mode Register
    volatile uint32_t OTYPER;   // Offset 0x04: Output Type Register
    volatile uint32_t OSPEEDR;  // Offset 0x08: Output Speed Register
    volatile uint32_t PUPDR;    // Offset 0x0C: Pull-Up / Pull-Down Register
    volatile uint32_t IDR;      // Offset 0x10: Input Data Register
    volatile uint32_t ODR;      // Offset 0x14: Output Data Register
} GPIO_TypeDef;

/* --- HARDWARE BASE ADDRESSES --- */
#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830U)
#define GPIOC       ((GPIO_TypeDef *)0x40020800U)

/* --- FLASH-STORED KEYPAD LAYOUT --- */
static const char KEYMAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

/* --- DEBUGGER INSPECTION VARIABLE --- */
/* Marked volatile so you can watch it live in VS Code / GDB without optimization */
volatile char last_key_pressed = 0;

/**
 * @brief  Rough software delay for switch debouncing.
 * @note   Assumes default 16 MHz HSI clock. Production firmware replaces this
 *         with a hardware timer (SysTick or TIMx) to avoid blocking the CPU.
 */
static void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < (ms * 2000U); i++) {
        /* Intentional empty loop; volatile prevents compiler deletion */
    }
}

/**
 * @brief  Initializes GPIOC pins for 4x4 matrix keypad scanning.
 */
static void keypad_init(void) {
    /* 1. Enable Clock for GPIOC (Bit 2 of RCC_AHB1ENR) */
    RCC_AHB1ENR |= (1U << 2);

    /* 2. Configure Rows (PC0 - PC3) as General Purpose Output ('01') */
    GPIOC->MODER &= ~(0xFFU << 0);   // Clear bits 0 to 7
    GPIOC->MODER |=  (0x55U << 0);   // Set 0b01010101 (Output mode for PC0-PC3)

    /* 3. Configure Columns (PC4 - PC7) as Input ('00') */
    GPIOC->MODER &= ~(0xFFU << 8);   // Clear bits 8 to 15 (Input mode for PC4-PC7)

    /* 4. Enable Internal Pull-Up Resistors ('01') on Columns (PC4 - PC7) */
    GPIOC->PUPDR &= ~(0xFFU << 8);   // Clear bits 8 to 15
    GPIOC->PUPDR |=  (0x55U << 8);   // Set 0b01010101 (Pull-up for PC4-PC7)

    /* 5. Set all Row outputs HIGH initially */
    GPIOC->ODR |= 0x0FU;             // Set bits 0 to 3 to '1'
}

/**
 * @brief  Scans the 4x4 matrix once and returns the pressed key, or 0 if none.
 */
static char keypad_scan(void) {
    for (uint8_t row = 0; row < 4; row++) {
        /* Reset all rows HIGH, then pull ONLY the current row LOW */
        GPIOC->ODR |=  0x0FU;
        GPIOC->ODR &= ~(1U << row);

        /* Check all 4 columns (PC4 through PC7) */
        for (uint8_t col = 0; col < 4; col++) {
            /* If the column reads LOW (0), a key is bridging this row & column */
            if (!(GPIOC->IDR & (1U << (col + 4)))) {
                delay_ms(200);       // 200ms debounce delay
                return KEYMAP[row][col];
            }
        }
    }
    return 0; // No key pressed
}

int main(void) {
    keypad_init();

    while (1) {
        char key = keypad_scan();
        if (key != 0) {
            last_key_pressed = key;
        }
    }
}