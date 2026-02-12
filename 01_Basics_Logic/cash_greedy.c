/**
 * @file    cash_greedy.c
 * @author  Fatih Kaan GÖKTÜRK
 * @date    12 Feb 2026
 * @brief   Solves the Change-Making Problem using a Greedy Algorithm.
 *
 * @details
 * Calculates the minimum number of coins required to give a user change.
 * Implements a Greedy strategy prioritizing larger denominations first.
 *
 * - Denominations: 25¢, 10¢, 5¢, 1¢
 * - Algorithm: Greedy Approach
 * - Time Complexity: O(N) (Where N is the amount of change)
 */
#include<stdio.h>
int main(void){
    int owed=0;
    int quarters=0;
    int tens=0;
    int fives=0;
    int ones=0;
    int count=0;
    printf("Change owed: ");
    scanf("%d",&owed);
    while(owed!=0){
        if(owed>=25){
            quarters=owed/25;
            owed=owed-quarters*25;
        }
        else if(owed>=10){
            tens=owed/10;
            owed=owed-tens*10;
        }
        else if(owed>=5){
            fives=owed/5;
            owed=owed-fives*5;
        }
        else{
            ones=owed;
            owed=0;
        }
    }
    int givenCoins=ones+fives+tens+quarters;
    printf("%d",givenCoins);

    return 0;
}