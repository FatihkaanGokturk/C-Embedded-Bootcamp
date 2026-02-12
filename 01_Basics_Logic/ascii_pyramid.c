/**
 * @file    ascii_pyramid.c
 * @author  Fatih Kaan GÖKTÜRK
 * @date    11 Feb 2026
 * @brief   Right-aligned ASCII pyramid generator with input validation.
 */
#include<stdio.h>
int main(void){
    int height;
    // Trap the user in a loop until they provide a safe hardware display limit
    do{
        printf("Height:");
        scanf("%d",&height);
    } while(height < 1 || height > 8);
    //creating rows dependent on the variable user gave
    for(int row = 0; row < height ; row++){
        //creating spaces for aligning pyramid to the right side
        for(int space = 0 ; space < height - row - 1 ; space++){
            printf(" ");
        }
        //adding hashes
        for(int hash = 0; hash < row + 1 ; hash++){
            printf("#");
        }
        //going to next line after loops
        printf("\n");
    }
    return 0;
}