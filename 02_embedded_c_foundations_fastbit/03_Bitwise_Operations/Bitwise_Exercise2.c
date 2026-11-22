#include<stdint.h>
#include<stdio.h>
int32_t result;
int32_t number;
int main(void){
    //make 4 abd 7th 1 using xor ? 
    printf("Give me the number:\n");
    scanf("%d",&number);
    result=number|0x90;
    printf("Result is: 0x%x",result);
}