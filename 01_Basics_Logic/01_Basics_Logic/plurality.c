/**
 * @file plurality.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-03-10
 * @brief Checks if input matches a valid candidate and increments their vote total.
 * @param name Pointer to the character array containing the voter's input.
 * @return true if candidate exists, false if candidate is invalid.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/**
 * @def MAXLEN, MAX
 * @brief Maximum allowed buffer size for standard input allocation.
 */
#define MAXLEN 100
#define MAX 9

/**
 * @struct candidate
 * @brief Container associating a candidate's name pointer with their active vote tally.
 */
typedef struct
{
    char *name;
    int votes;
} candidate;

candidate candidates[MAX];

int candidate_count;


bool vote(char *name);
void print_winner(void);
int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %d\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count; 
    printf("Number of voters: ");
    scanf("%d",&voter_count);
    for (int i = 0; i < voter_count; i++)
    {
        char name[MAXLEN] ;
        printf("Vote: ");
        scanf("%99s",name);
    
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}
/**
 * Function that checks if input is valid candidate or not using strcmp function
 */
bool vote(char *name)
{
    for(int i=0;i<candidate_count;i++){
        if (strcmp(name,candidates[i].name)==0)
        {
            candidates[i].votes++;
            return true; 
        }
}
return false;
}



/**
 * @brief Executes a two-pass linear search to find and print the winner(s) without O(N log N) sorting overhead.
 */
void print_winner(void)
{
    int max_voted=0;
    for(int i=0;i<candidate_count;i++){
        if(candidates[i].votes>max_voted)
            max_voted=candidates[i].votes;
    }
    for(int i=0;i<candidate_count;i++){
        if(candidates[i].votes==max_voted)
            printf("%s\n",candidates[i].name);
    }
    return;
}