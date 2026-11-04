/**
 * @file Preventing_Stack_Overflow.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-11-04
 * @brief Demonstrate a stack overflow example and showing a way to prevent using pointers 
 */
#include<stdint.h>
//Imagine this struct contains 100 bytes of complicated settings.

typedef struct{
    uint32_t baud_rate;
    uint8_t parity;
    //.. imagine 90 more bytes of data here 
}UART_Config_t;

//BAD way
//this forces the CPU to copy all 100 bytes into SRAM
void Bad_init(UART_Config_t config_copy){}

//GOOD way using *
//The compiler builds a box to hold the street address of a UART configration 
void Good_init(UART_Config_t *config_pointer){

if(config_pointer->baud_rate == 115200){
    //do something 
    }
}
void main(void){
    UART_Config_t my_settings ={115200,0};
    //we are using & because we dont want it to copy our data but to take data's address 
    Good_init(&my_settings);
    return 0;
}