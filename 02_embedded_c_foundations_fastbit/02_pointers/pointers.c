/**
 * @file pointers.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-04
 * @brief Demonstrate pointer assignment, memory addresses, and variable modification.
 */
#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t sensor_data = 50;
    uint8_t *mem_address = &sensor_data;

    printf("--- Before Modification ---\n");
    printf("Initial sensor_data value:        %u\n", sensor_data);
    printf("Memory address of sensor_data:    %p\n", (void *)&sensor_data);

    // Modify the variable value via pointer dereference
    *mem_address = 99;

    printf("\n--- After Modification via Pointer ---\n");
    printf("Address stored in mem_address:    %p\n", (void *)mem_address);
    printf("Dereferenced value (*mem_address): %u\n", *mem_address);
    printf("Verified sensor_data value:       %u\n", sensor_data);

    return 0;
}