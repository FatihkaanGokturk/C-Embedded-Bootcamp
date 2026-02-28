/**
 * @file substitution.c
 * @author Fatih Kaan GÖKTÜRK
 * *@date 2026-02-28
 * @brief A memory-safe, embedded-friendly implementation of the Substitution cipher.
 *
 * This module encrypts a user-provided plaintext string using a 26-character
 * alphabetic key. It is designed with embedded systems principles in mind, 
 * utilizing in-place pointer arithmetic, O(1) auxiliary space validation, 
 * and hardware-efficient character manipulation without relying on heavy 
 * standard libraries where avoidable.
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
/**
 * @def maxlen
 * @brief Maximum allowed buffer size for standard input allocation.
 */
#define maxlen 1000
/**
 * @brief Main execution function for the substitution encryption algorithm.
 *
 * Validates the cryptographic key provided via command-line arguments to ensure
 * it contains exactly 26 unique alphabetic characters. Upon successful validation,
 * it prompts the user for plaintext and outputs the ciphertext using an O(N) 
 * lookup table approach.
 *
 * @param argc The number of command-line arguments.
 * @param argv Array of command-line argument strings. argv[1] must be the 26-char key.
 * @return int Returns 0 on successful encryption, or 1 if validation fails.
 */
int main(int argc, char *argv[]){
    char sentence[maxlen];
    /* =====================================================================
     * PHASE 1: INITIALIZATION & IN-PLACE VALIDATION
     * ===================================================================== */
    // Guard Clause 1: Ensure strict argument count to prevent segmentation faults
     if(argc!=2){
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if(strlen(argv[1])!=26){
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    char *traveler=argv[1];
    while(*traveler){
        char c=*traveler;
        if(!isalpha(c)){
            return 1;
        }
        char *traveler2 = traveler + 1;
        while(*traveler2){
            if(toupper(*traveler2)==toupper(*traveler)){
                return 1;
            }
            traveler2++;
        }
        traveler++;
    }
    printf("plaintext: ");
    fgets(sentence,maxlen,stdin);// Safely read user input into the predefined buffer
    // Initialize pointer to traverse the user-provided plaintext
    char *text_traveler = sentence;
    printf("ciphertext: ");
    // Process the text character by character
    while(*text_traveler){
        char i=*text_traveler;
        if (isupper(i)){
            // Calculate zero-based index by shifting ASCII offset (A=0, B=1...)
            i=i-'A';
            // Map index to the lookup table, maintain uppercase format, and output directly
            putchar(toupper(argv[1][(int)i]));
        }
        else if(islower(i)){
            // Calculate zero-based index for lowercase offset
            i=i-'a';
            // Map index to the lookup table, maintain lowercase format, and output directly
            putchar(tolower(argv[1][(int)i]));
        }
        else{
            putchar(i);// Output raw character (spaces, punctuation, \n) without modification
        }
        text_traveler++;// Advance to the next memory address

    }
    return 0;// Return success status to the OS

}