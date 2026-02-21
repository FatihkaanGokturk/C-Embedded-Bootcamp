/**
 * @file    scrabble.c
 * @author  Fatih Kaan GÖKTÜRK
 * @date    21 Feb 2026
 * @brief   Scrabble Game Scorer
 * This program calculates the score of two words based on standard Scrabble
 * letter values and determines which player wins.
 */
#include<stdio.h>
int main(void){
    // Array containing point values for each letter from A to Z
    int values[]={1	,3	,3	,2	,1	,4	,2	,4	,1	,8	,5	,1	,3	,1	,1	,3	,10	,1	,1	,1	,1	,4	,4	,8	,4	,10};
    
    char word1[50];
    char word2[50];
    int player1=0, player2=0, i=0;
    // Prompt users for their words
    printf("Player1: ");
    scanf("%s",word1);
    printf("Player2: ");
    scanf("%s",word2);
    // Calculate Player 1's score
    while(word1[i]>0){
        // Check if the character is a lowercase letter (ASCII 97-122)
        if(word1[i] >= 97 && word1[i] <= 122){
            // Map the ASCII value to the 0-25 index of the values array
            player1 += values[word1[i]-'A'-' '];
            i++;
    }
        // Check if the character is an uppercase letter (ASCII 65-90)
        else if (word1[i]>=65 &&word1[i]<=90){
            player1+=values[word1[i]-'A'];
            i++;
    }
        // Ignore non-alphabetic characters (punctuation, numbers, etc.)
        else{
            i++;
        }
    }
    // Reset index counter for Player 2
    i=0;
    // Calculate Player 2's score
    while(word2[i]>0){
        if(word2[i] >= 97 && word2[i] <= 122){
            player2 += values[word2[i]-'A'-' '];
            i++;
    }
        else if (word2[i]>=65 &&word2[i]<=90){
            player2+=values[word2[i]-'A'];
            i++;
    }
        else{
            i++;
        }
    }
    // Compare scores and print the result
    if(player1>player2){
        printf("Player 1 wins! \n");
    }
    else if(player2>player1){
        printf("Player 2 wins! \n");
    }
    else{
        printf("Tie! \n");
    }
    return 0;
}