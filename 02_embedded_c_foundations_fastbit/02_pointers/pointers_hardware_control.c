/**
 * @file pointers_hardware_control.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-04
 * @brief Demonstrate an hardware control(memory mapping) example via pointers.
 */
#include <stdint.h>
int main(void){
    //Here compiler thinks that 0x40020014 is a random number 
    uint32_t raw_number=0x40020014;
    //We explicitly cast this number to a poiner
    //We are telling compiler: "This is not a math number
    //This is address for a 32-bit volatile hardware register."
    volatile uint32_t *gpio_odr_pointer=(volatile uint32_t) raw_number;
    //We use * to travel that exact physical address in the silicon .
    //we open the door, adn we use bitwise or flip bit to 5 to 1
    //the physical LED on your Nucleo board instantly turns on 
    *gpio_odr_pointer |=(1<<5);
    return 0;
}