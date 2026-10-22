#include <stdint.h>
#include <stdio.h>

/**
 * @file floating_point_traps.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 22 October 2026
 * @brief Demonstrates the performance and precision traps of float and double in bare-metal ARM Cortex-M programming.
 */


 //TRAP 1 : THE IMPLICIT DOUBLE PROMOTION
void Bad_Sensor_Math(void){
    float sensor_val=24.5;
    /* 
     * THE BUG: is "1.8" and "32.0" are DOUBLE literals(64 bit) * The compiler implicitly cast 32 bit variable to 64 bit
     * this wastes hundreds of CPU cycles */
    float fahrenheit=(sensor_val * 1.8)+32.0;
}
void Good_Sensor_Math(void){
    float sensor_val=24.5;
    /**
     * THE FIX: Add "f" suffix to all literal numbers.
     * The compiler keeps everything in 32 bit space.
     * On an STM32F3 this executes instantly in the hardware FPU.
     */
    float fahrenheit=(sensor_val * 1.8f) +32.0f;
}

//TRAP 2: CATASTROPHIC CANCELLATION (The GPS problem)

void GPS_Precision_Demp(void){
    float lat_float =50.870334f;
    lat_float =lat_float +0.000001f;
    //The problem is float is 32 bit and only tracks 7 significant bits so at this situation 0.000001 value was lost


    double lat_double = 50.870334;
    lat_double =lat_double +0.000001;
}



//TRAP 3 :EXPLUCUT CASTING WITH MIXED TYPES

void Process_Raw_ADC(void){
    uint16_t raw_adc=2048;// 12-bit ADC reading
    float ref_voltage =3.3f; //System reference voltage

    //The problem is 2049/3095 would equal 0 
    // To prevent that explicitly cast the values
    float actual_voltage = ((float)raw_adc/4095.0f)*ref_voltage;
}