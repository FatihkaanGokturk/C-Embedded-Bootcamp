/**
 * @file    credit.c
 * @author  Fatih Kaan GÖKTÜRK
 * @date    12 Feb 2026
 * @brief   Validates credit card numbers using Luhn's Algorithm (Checksum).
 *
 * @details
 * This program checks the validity of a credit card number based on:
 * 1. Length (13, 15, or 16 digits)
 * 2. Checksum (Luhn's Algorithm / Mod 10)
 * 3. Issuer Identification Number (IIN) / Prefix matching
 *
 * - Supported Cards: AMEX, MASTERCARD, VISA
 * - Input: Long Long Integer (64-bit) to handle up to 16 digits.
 */
#include<stdio.h>

/**
 * Calculates the number of digits in a credit card number.
 * @param n: The credit card number
 * @return: Total count of digits
 */
long countnumber(long long n){
    int count = 0;
    // Continuously divide by 10 to strip off the last digit until 0
    while(n != 0){
        n = n / 10;
        count++;
    }
    return count;
}

/**
 * Extracts the first two digits (Prefix) of the card number.
 * Used for identifying the card issuer (e.g., 34 for Amex, 51 for MasterCard).
 */
int find2dig(long long number){
    long long extraction = 1;
    int count = countnumber(number);
    
    // Create a divisor (10^(n-2)) to isolate the first two digits
    // Example: For 12345 (count 5), we need divisor 1000 to get 12.
    for(int j = 0; j < count - 2; j++){
        extraction *= 10;
    }

    int twodigits = number / extraction; 
    return twodigits;
}

/**
 * Helper function for Luhn's Algorithm.
 * Multiplies a digit by 2. If the result is double-digit (e.g., 16),
 * adds the digits together (1 + 6 = 7).
 */
long long luhndouble(long long n){
    n = n * 2;
    // If product > 9, sum the digits (e.g., 18 -> 1 + 8 = 9)
    if(n > 9){
        n = n % 10 + n / 10;
        return n;
    }
    else{
        return n;
    }
}

/**
 * Main implementation of Luhn's Algorithm.
 * Traverses the number from right to left, doubling every second digit.
 * @return: 1 if valid (sum % 10 == 0), 0 otherwise.
 */
int isValid(long long number){
    int count = countnumber(number);
    int sum = 0;
    int temp;

    // Loop through each digit from right to left
    for (int i = 0 ; i < count ; i++ ){
        temp = number % 10;      // Get the last digit
        number = number / 10;    // Remove the last digit
        
        // Check if it's an odd position (every second digit from the right)
        // Note: i starts at 0, so i%2==1 represents the 2nd, 4th, 6th... digits
        if(i % 2 == 1){
            sum += luhndouble(temp); // Double and add per Luhn's rule
        }
        else{
            sum += temp;             // Just add the digit
        }
    }
    
    // If the total sum ends in 0, the number is valid
    if(sum % 10 == 0){
        return 1; // True
    }
    else{
        return 0; // False
    }
}

int main(void){
    int count;
    long long number;
    
    // INPUT VALIDATION LOOP
    // Ensure the user enters a potential card number length (13, 15, or 16)
    // Note: This traps the user until a "plausible" length is entered.
    do{
        printf("Number: ");
        scanf("%lld", &number);
        count = countnumber(number);
    }
    while( count != 16 && count != 13 && count != 15 );

    long long numbercopy = number; // Keep original number for prefix check
    int validity = isValid(number);

    // STEP 1: Check Checksum Validity
    if(validity == 0){
        printf("INVALID\n");
        return 0;
    }
    else{
        // STEP 2: Check Card Issuer based on Prefixes
        int twodigits = find2dig(numbercopy);

        // AMEX: 15 Digits, Starts with 34 or 37
        if(count == 15 && (twodigits == 34 || twodigits == 37)){
            printf("AMEX\n");
        }
        // MASTERCARD: 16 Digits, Starts with 51-55
        else if(count == 16 && (twodigits >= 51 && twodigits <= 55)){
            printf("MASTERCARD\n");
        }
        // VISA: 13 or 16 Digits, Starts with 4
        // Logic: twodigits / 10 gives the first digit (e.g., 42 / 10 = 4)
        else if((count == 13 || count == 16) && (twodigits / 10 == 4)){
            printf("VISA\n");
        }
        else{
            printf("INVALID\n");
        }
    }
    return 0;
}