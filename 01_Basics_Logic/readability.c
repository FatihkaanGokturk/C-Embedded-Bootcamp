/**
 * @file    scrabble.c
 * @author  Fatih Kaan GÖKTÜRK
 * @date    24 Feb 2026
 * @brief  Text Readability Analyzer (Coleman-Liau Index)
 * * Architecture & Optimization Notes (Embedded Systems Focus):
 * - Single-pass parsing (O(N) complexity) using pointer arithmetic to save CPU cycles.
 * - Memory-safe input handling via fgets() to prevent buffer overflow vulnerabilities.
 * - Library-independent rounding (+0.5 trick) avoids <math.h> overhead, saving Flash/ROM memory.
 */
#include<stdio.h>
// Defines a safe maximum buffer size to handle full paragraphs without overflow
#define maxlen 1000
int main(void) {
    // Initialized as doubles to prevent truncation during integer division later
    double letter_count=0;
    double sentence_count=0;
    double word_count=1;// Starts at 1 since words are separated by spaces
    char sentence[maxlen];
    printf("Text: ");
    // Safe input reading: prevents writing beyond the allocated memory limits
    fgets(sentence,maxlen,stdin);
    // Pointer for efficient memory traversal (avoids array indexing overhead)
    char *traveler=sentence;
    // Single-pass logic: analyzes characters simultaneously to minimize branching
    while(*traveler){
        char c=*traveler;
        if(c>='a'&&c<='z' || c>='A' && c<= 'Z'){
            letter_count++;
        }
        else if(c == ' '){
            word_count++;
        }
        else if(c =='.' || c== '?' || c== '!'){
            sentence_count++;
        }
        traveler++;// Move to the next memory address
    }
    // Coleman-Liau Index calculation
    // L: Average number of letters per 100 words
    double avnumletter=(letter_count/word_count)*100;
    // S: Average number of sentences per 100 words
    double avnumsentences=(sentence_count/word_count)*100;
    double index = 0.0588 * avnumletter - 0.296 * avnumsentences - 15.8;
    // Hardware-friendly rounding trick: avoids including hefty <math.h> library
    int rounded_index=(int)(index+0.5);
    // Output formatting based on the calculated grade level
    if(rounded_index<1){
        printf("Before Grade 1\n");
    }

    else if(rounded_index>=16){
        printf("Grade 16+\n");
    }

    else{
        printf("Grade %d\n",rounded_index);
    }

    return 0;
}