#include <stdio.h>
#include <stdint.h>
int main(void){
    uint8_t sensor_data=50;
    uint8_t *memadress;
    memadress=&sensor_data;
    *memadress=99;
    printf("%p",&sensor_data);
    return 0;
}