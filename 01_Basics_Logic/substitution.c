#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define maxlen 1000
int main(int argc, char *argv[]){
    char sentence[maxlen];
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
    fgets(sentence,maxlen,stdin);
    char *text_traveler = sentence;
    printf("ciphertext: ");
    while(*text_traveler){
        char i=*text_traveler;
        if (isupper(i)){
            i=i-'A';
            putchar(toupper(argv[1][(int)i]));
        }
        else if(islower(i)){
            i=i-'a';
            putchar(tolower(argv[1][(int)i]));
        }
        else{
            putchar(i);
        }
        text_traveler++;

    }
    return 0;

}