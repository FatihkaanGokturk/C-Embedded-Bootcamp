#include <stdio.h>
#include <stdint.h>

// This is our mock 16-bit hardware register. It boots up as all zeros.
uint16_t MOTOR_CONFIG = 0x0000;

void Print_Binary(uint16_t reg) {
    // A helper function to print the 16 bits so you can see your math working!
    printf("Register: 0x%04X | Binary: ", reg);
    for (int i = 15; i >= 0; i--) {
        printf("%d", (reg >> i) & 1);
        if (i % 4 == 0) printf(" "); // Add a space every 4 bits for readability
    }
    printf("\n");
}

int main(void) {
    printf("--- Commit 1: Boot ---\n");
    Print_Binary(MOTOR_CONFIG);
    //Reversed
    MOTOR_CONFIG |= (1<<3);  
    Print_Binary(MOTOR_CONFIG);
    // Speed ID
    MOTOR_CONFIG |= (5<<0) |(9<<4);
    Print_Binary(MOTOR_CONFIG);
    return 0;
}