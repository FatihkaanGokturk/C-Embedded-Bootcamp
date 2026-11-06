/**
 * @file Motor_Config.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-06
 * @brief Demonstrate bitwise register manipulation for motor control,
 *        including setting, packing, extracting, clearing, and toggling bits.
 */
#include <stdio.h>
#include <stdint.h>

// This is our mock 16-bit hardware register. It boots up as all zeros.
uint16_t MOTOR_CONFIG = 0x0000;

void Print_Binary(uint16_t reg) {
    printf("Register: 0x%04X | Binary: ", reg);
    for (int i = 15; i >= 0; i--) {
        printf("%d", (reg >> i) & 1);
        if (i % 4 == 0) printf(" "); 
    }
    printf("\n");
}

int main(void) {
    printf("--- Commit 1: Boot ---\n");
    Print_Binary(MOTOR_CONFIG);
    
    /* STEP 2: Set Direction Bit to Reverse (Bit 3) */
    MOTOR_CONFIG |= (1U << 3);  
    Print_Binary(MOTOR_CONFIG);
    
    /* STEP 3: Pack Speed (Bit 0) and Motor ID (Bit 4) */
    MOTOR_CONFIG |= (5U << 0) | (9U << 4);
    Print_Binary(MOTOR_CONFIG);

    /* STEP 4: Extract Fault Code (Bits 15:8) */
    MOTOR_CONFIG |= (0xAB << 8); // Hardware injects fault
    uint8_t current_fault = (MOTOR_CONFIG >> 8);
    printf("Fault Code: 0x%02X\n", current_fault);
    Print_Binary(MOTOR_CONFIG);
    
    /* STEP 5: Safe Clear of Speed Bits (Bits 2:0) */
    // Using Bitwise AND NOT to crush bits 0, 1, and 2 down to zero.
    MOTOR_CONFIG &= ~((1U << 0) | (1U << 1) | (1U << 2));
    Print_Binary(MOTOR_CONFIG);
    
    /* STEP 6: Toggle Direction Bit (Bit 3) */
    // Using Bitwise XOR to flip the direction from Reverse to Forward.
    MOTOR_CONFIG ^= (1U << 3);
    Print_Binary(MOTOR_CONFIG);

    return 0;
}