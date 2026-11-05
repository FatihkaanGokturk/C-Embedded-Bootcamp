/**
 * @file i2c_config_mutation.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-05
 * @brief Demonstrate struct modification through pointer dereference and arrow operator.
 */

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t device_address;
    uint32_t speed_hz;
} I2C_Config_t;

/**
 * @brief Validates bus speed and updates the peripheral target address via pointer.
 * @param config_pointer Pointer to the mutable I2C configuration structure.
 */
void I2C_Init_Config(I2C_Config_t *config_pointer) {
    // Arrow operator (->) dereferences pointer and accesses member directly
    if (config_pointer->speed_hz == 400000) {
        printf("Fast mode (400kHz) detected. Assigning default address 0x3C.\n");
        config_pointer->device_address = 0x3C;
    }
}

int main(void) {
    I2C_Config_t my_sensor = {0x11, 400000};

    printf("Device address before init: 0x%02X\n", my_sensor.device_address);

    // Pass struct address (&) to modify original instance in-place
    I2C_Init_Config(&my_sensor);

    printf("Device address after init:  0x%02X\n", my_sensor.device_address);

    return 0;
}