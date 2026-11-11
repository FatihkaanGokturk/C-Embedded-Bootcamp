/**
 * @file type_qualifiers_practice.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-11
 * @brief Demonstrate embedded type qualifiers (const, volatile) for memory placement and hardware protection.
 */

#include <stdint.h>

/**
 * @brief Engine RPM threshold lookup table placed strictly in Flash (ROM) to preserve SRAM.
 * @note Marking this array 'const' ensures the compiler allocates it to .rodata (Flash memory).
 */
const uint16_t rpm_thresholds[500] = {1000, 1500, 2000, /* ... */};

/**
 * @brief Global motor fault flag modified asynchronously inside an Interrupt Service Routine (ISR).
 * @note 'volatile' prevents the compiler from optimizing reads into CPU registers, 
 *       forcing a re-read from SRAM every time the main loop checks this flag.
 */
volatile uint8_t motor_fault_flag = 0;

/**
 * @brief Pointer to an STM32 hardware timer counter register (read-only hardware counter).
 * @note 'const volatile' ensures the software cannot overwrite the peripheral register ('const'),
 *       while signaling that hardware increments it autonomously on every tick ('volatile').
 */
const volatile uint32_t *hardware_timer = (const volatile uint32_t *)0x40000024U;