#include<stdio.h>
int main(void){
    int height;
    do{
        printf("Height:");
        scanf("%d",&height);
    } while(height<1 ||height>8);
    
    for(int row=0;row<height;row++){
        for(int space=0;space<height-row-1;space++){
            printf(" ");
        }
        for(int hash=0;hash<row+1;hash++){
            printf("#");
        }
        printf("\n");
    }
    return 0;
}