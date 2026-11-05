/**
 * @file uart_buffer_parser.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-05
 * @brief Traverse a UART RX buffer using pointer arithmetic and print raw hex data.
 */

#include <stdio.h>
#include <stdint.h>

int main(void) {
    // Simulated 6-byte UART receive frame (e.g., packet header, payload, checksum)
    uint8_t uart_rx_buffer[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    
    // Assign base address of array to pointer (uart_rx_buffer decays to &uart_rx_buffer[0])
    uint8_t *ptr = uart_rx_buffer;

    for (int i = 0; i < 6; i++) {
        // Dereference ptr to extract byte (*ptr) and format address as pointer (%p)
        printf("Index [%d] | Address: %p | Data: 0x%02X\n", i, (void *)ptr, *ptr);

        // Advance pointer to the next contiguous byte in SRAM
        ptr++;
    }
    
    return 0;
}