/**
* @file    ceasar.c
 * @author Fatih Kaan GÖKTÜRK
 * @date   25 Feb 2026
 * @brief  Caesar Cipher Encoder
 *         Architecture & Optimization Notes (Embedded Systems Focus):
 *         - Memory-Safe Input: Uses fgets() to prevent buffer overflow vulnerabilities.
 *         - Single-Pass Validation: Validates CLI arguments using pointer traversal (O(N)) without string.h.
 *         - In-Place ASCII Shift: Performs cryptographic shifts directly on ASCII values, 
 *         -avoiding heavy lookup tables or dynamic memory allocation (malloc).
 *         - Lookup Efficiency: Utilizes <ctype.h> for O(1) character type checking.
 */
#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
// Defines a safe maximum buffer size to handle inputs without overflow
#define maxlen 1000
int main(int argc, char *argv[]){
    char sentence[maxlen];
    // Check if exactly one command-line argument is provided
    if(argc ==2){
        // Pointer to traverse the provided encryption key
        char *traveler= argv[1];
        // Validate that the key consists only of digits
        while (*traveler){
            char c= *traveler;
            // ASCII check: if character is not between '0' (48) and '9' (57)
            if(c<48|| c>57){
                printf("Usage: ./caesar key\n");
                return 1;// Exit with error code
            }
            traveler++;// Move to the next character in memory
        }
        // Convert the validated string key into an integer
        int key=atoi(argv[1]);
        printf("plaintext: ");
        fgets(sentence,maxlen,stdin);
        printf("ciphertext: ");
        // Pointer to traverse the input text for encryption
        char *traveler2=sentence;
        while(*traveler2){
            char i=*traveler2;
            // Route 1: Uppercase letters
            if(isupper(i)){
                i=i-'A';
                i=(i+key)%26;
                i=i+'A';
                printf("%c",i);
        }
        // Route 2: Lowercase letters
        else if(islower(i)){
            i=i-'a';
            i=(i+key)%26;
            i+='a';
            printf("%c",i);
        }
        // Route 3: Non-alphabetic characters (spaces, punctuation, \n)
        else{
            printf("%c",i);//print as is 
        }
        traveler2++;// Move to the next memory address   
        }
    }
    // Handle incorrect number of command-line arguments
    else{
        printf("Usage: ./caesar key");
        return 1;
    }
    return 0;// Execution successful
}