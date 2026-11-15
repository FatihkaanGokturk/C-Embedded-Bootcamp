/**
 * @file      packet_decoder.c
 * @author    Fatih Kaan GÖKTÜRK
 * @brief     Decodes a 32-bit network packet into individual bit-fields.
 */

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

/**
 * @brief Packet structure mapping the 32-bit protocol using bit-fields.
 *        Ordered from LSB to MSB to match ARM GCC compiler packing.
 */
typedef struct {
    uint32_t crc       : 2;
    uint32_t status    : 1;
    uint32_t payload   : 12;
    uint32_t bat       : 3;
    uint32_t sensor    : 3;
    uint32_t longAddr  : 8;
    uint32_t shortAddr : 2;
    uint32_t addrMode  : 1;
} Packet_t; // Appended _t to indicate this is a Type definition

/**
 * @brief Memory Overlay Union for Type Punning.
 *        This safely bridges the gap between raw 32-bit data and the struct 
 *        without needing risky pointer casts.
 */
typedef union {
    uint32_t raw_data;
    Packet_t decoded;
} PacketDecoder_t;

int main(void) {
    // 1. Move the variable inside main(). Never use globals unless required by an ISR!
    PacketDecoder_t packet;
    
    printf("Enter 32-bit packet value (Hex):\n");
    
    // 2. Read the user input directly into the raw_data side of the union.
    // Notice the space between "%" and SCNx32 to ensure proper macro expansion.
    scanf("%" SCNx32, &packet.raw_data);
    
    // 3. The data is instantly available on the 'decoded' side of the union!
    // Using %u instead of %d because these are Unsigned integers.
    printf("CRC       : %u\n", packet.decoded.crc);
    printf("Status    : %u\n", packet.decoded.status);
    
    // Payload and Addresses are often printed in Hex (%#x) for easier debugging
    printf("Payload   : %#x\n", packet.decoded.payload); 
    printf("Bat       : %u\n", packet.decoded.bat);
    printf("Sensor    : %u\n", packet.decoded.sensor);
    printf("LongAddr  : %#x\n", packet.decoded.longAddr);
    printf("ShortAddr : %#x\n", packet.decoded.shortAddr);
    printf("AddrMode  : %u\n", packet.decoded.addrMode);
    
    return 0;
}