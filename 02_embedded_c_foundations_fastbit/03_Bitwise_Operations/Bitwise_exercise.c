#include<stdint.h>
#include<stdio.h>
uint32_t integer1;
uint32_t integer2;
int main(void){

    printf("Enter integer no.1: \n");
    scanf("%d",&integer1);
    printf("Enter integer no.2\n");
    scanf("%d",&integer2);
    printf("Result of and operator: %d\n",integer1&&integer2);
    printf("Result of or operator: %d\n",integer1||integer2);
    printf("Result of xor operator: %d\n",integer1^integer2);
    printf("Result of not operator:%d %d\n",~integer1, ~integer2);
    return 0;
}

