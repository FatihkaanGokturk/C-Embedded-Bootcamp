/**
 * @file pointer_arithmetic_buffer.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-04
 * @brief Demonstrate pointer arithmetic and sequential buffer traversal.
 */

#include <stdint.h>
#include <stdio.h>

void Sensor_Data(void) {
    // 3-byte contiguous sensor payload in SRAM
    uint8_t buffer[3] = {10, 20, 30};

    // Point to the base address of the array (buffer decays to &buffer[0])
    uint8_t *ptr = buffer;

    // --- Element 0 ---
    printf("Byte 0 -> Address: %p | Value: %u\n", (void *)ptr, *ptr);

    // Increment pointer: advances by sizeof(uint8_t) -> exactly 1 byte
    ptr = ptr + 1;
    printf("Byte 1 -> Address: %p | Value: %u\n", (void *)ptr, *ptr);

    // Increment again: advances to the final element
    ptr++;
    printf("Byte 2 -> Address: %p | Value: %u\n", (void *)ptr, *ptr);
}

int main(void) {
    Sensor_Data();
    return 0;
}