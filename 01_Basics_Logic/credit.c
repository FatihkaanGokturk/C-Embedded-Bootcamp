/**
 * @file    credit.c
 * @author  Fatih Kaan GÖKTÜRK
 * @date    12 Feb 2026
 * @brief   Validates credit card numbers using an optimized Luhn's Algorithm.
 *
 * @details
 * This bare-metal implementation checks the validity of a credit card based on:
 * 1. Length validation (13, 15, or 16 digits)
 * 2. Checksum validation (Luhn's Algorithm using a Look-Up Table)
 * 3. Issuer Identification Number (IIN) / Prefix matching
 *
 * - Supported Cards: AMEX, MASTERCARD, VISA
 * - Input Strategy: Reads input as a string buffer to prevent overflow
 * and eliminate expensive 64-bit hardware division.
 */
#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
/**
 * @brief Look-Up Table (LUT) for O(1) Luhn doubling.
 * * @details Maps a digit (0-9) directly to the sum of the digits of (digit * 2).
 * Eliminates the need for modulo and division operations during the checksum.
 */
uint8_t luhn_Boot[]={0,2,4,6,8,1,3,5,7,9};
/**
 * @brief Main execution loop for credit card validation.
 *
 * @details Safely reads a maximum 19-character string from standard input,
 * calculates the exact string length, performs a single-pass backward
 * traversal to calculate the Luhn checksum, and evaluates the IIN prefixes.
 *
 * @return int 0 upon successful execution, 1 on input failure.
 */
int main(void){
    char cc[20];
    printf("Number: \n");
    // Safely restrict input buffer to prevent memory overflow
    if(scanf("%19s",cc)!=1){
        return 1;
    }
    uint8_t len=0;
    int sum=0;
    uint8_t digit;
    uint8_t length=0;
    bool is_second=false;
    // Calculate string length
    while(cc[len]!='\0'){
        length++;
        len++;
    }
    // 1. Length Validation
    if (length !=13 && length != 16 && length!=15)
    {
        printf("INVALID!\n");
        return 0;
    }
    // 2. Luhn Checksum Calculation (Right-to-Left Traversal
    for(int i=length-1;i>=0;i--){
            digit =cc[i]-'0';
            if(!is_second){
                sum+=digit;
            }
            else{
                sum+=luhn_Boot[digit];
            }
            is_second=!is_second;
        }
    // Validate final checksum against Modulo 10
    if(sum%10!=0){
        printf("INVALID!\n");
        return 0;
    }
    // 3. Prefix / Issuer Identification
    if(length == 15 && cc[0]=='3' && (cc[1]=='4'||cc[1]=='7')){
        printf("AMEX\n");
    }
    else if(length==16 && cc[0]=='5' && cc[1]>'0' && cc[1]<'6'){
        printf("MASTERCARD \n");
    }
    else if( (length == 13|| length ==16 )&& cc[0]=='4'){
        printf("VISA\n");
    } 
    else{
        printf("INVALID");
        return 0;
    }
    return 0;
}