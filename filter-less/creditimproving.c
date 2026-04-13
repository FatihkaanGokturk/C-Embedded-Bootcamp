#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
static const uint8_t luhn_lut[10]={0,2,4,6,8,1,3,5,7,9};

int main(void){
    char cc[20];
    printf("Number: \n");
    if(scanf("%19s",cc)!=1){
        return 1;
    }
    uint8_t length=0;
    while(cc[length]!='\0'){
        if(cc[length]<'0'||cc[length]>'9'){
            printf("INVALID\n");
            return 1;
        }
        length++;
    }
    bool is_second=false;
    uint8_t sum=0;
    for(int i=length-1;i>=0;i--){
        uint8_t digit=cc[i]-'0';
        if(is_second){
            sum+=luhn_lut[digit];
        }
        else{
        sum+=digit;
    }
        is_second=!is_second;
    }
    if(sum%10!=0){
        printf("INVALID!\n");
        return 0;
    }
    if(length ==15 && cc[0]=='3' && ((cc[1]=='4') || (cc[1]=='7'))){
        printf("American Express\n");
    }
    else if(length==16 && cc[0]==5 && (cc[1] >= '1' && cc[1] <= '5')){
        printf("MasterCard");
    }
    else if((length==13 || length==16)&&cc[0]=='4'){
        printf("VISA");
    } 
    else{
        printf("INVALID!\n");
    }
    return 0;
}