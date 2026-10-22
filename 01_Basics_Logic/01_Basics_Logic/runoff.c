/**
 * @file runoff.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-03-11
 * @brief Checks inputs and ranks of it and validity of the votes checks if its tied or not and then prints the winner of election by rank system
 * @param name Pointer to the character array containing the voter's input.
 * @return true if candidate exists, false if candidate is invalid.
 */

#include <stdio.h>
#include<stdbool.h>
#include<string.h>
#include <stdint.h>

#define MAXLEN 100
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
uint8_t preferences[MAX_VOTERS][MAX_CANDIDATES];

/**
 * @struct candidate
 * @brief Container associating a candidate's name pointer with their active vote tally ,bool value of if it is eleminated
 */
typedef struct
{
    char *name;
    uint8_t votes;
    bool eliminated;
} candidate;


candidate candidates[MAX_CANDIDATES];


uint8_t voter_count;
uint8_t candidate_count;

/**
 * @brief Records a voter's preference if the candidate is valid.
 * * @param voter The index of the voter casting the ballot.
 * @param rank The rank preference being assigned (0 for first choice, etc.).
 * @param name The string name of the candidate being voted for.
 * @return true if the candidate exists and the vote was recorded.
 * @return false if the candidate's name is not on the ballot.
 */
bool vote(uint8_t voter, uint8_t rank, char *name);
void tabulate(void);
bool print_winner(void);
uint8_t find_min(void);
bool is_tie(uint8_t min);
void eliminate(uint8_t min);

int main(int argc, char *argv[])
{
    
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }


    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (uint8_t i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    printf("Number of voters: ");
    scanf("%hhu",&voter_count);
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    for (uint8_t i = 0; i < voter_count; i++)
    {

   
        for (uint8_t j = 0; j < candidate_count; j++)
        {
            char name[MAXLEN] ;
            printf("Rank %i: ", j + 1);
            scanf("%s",name);
            
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }
    while (true)
    {
        tabulate();
        bool won = print_winner();
        if (won)
        {
            break;
        }

        uint8_t min = find_min();
        bool tie = is_tie(min);
        if (tie)
        {
            for (uint8_t i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }
        eliminate(min);
        for (uint8_t i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}
/**
 * @brief that checks if input is valid candidate or not using strcmp function
 */
bool vote(uint8_t voter, uint8_t rank, char *name)
{
    for(uint8_t i=0;i<candidate_count;i++){
        if(strcmp(candidates[i].name,name)==0)
            {preferences[voter][rank]=i;
             return true;
            }
        }
    return false;
}
/**
 * @brief function that increments votes of candidates
 */
void tabulate(void)
{   
    for(uint8_t i=0;i<voter_count;i++){
        for(uint8_t j=0;j<candidate_count;j++){
             if((candidates[preferences[i][j]].eliminated)==true)
             continue;
             else{
                candidates[preferences[i][j]].votes++;
        }
        break;
        }
       
}
    return;
}

/**
 * @brief checks if there is a candidate has more than %50 of votes and prints it out
 */
bool print_winner(void)
{   
    for(uint8_t i=0;i<candidate_count;i++){
        if(candidates[i].eliminated==false && candidates[i].votes>voter_count/2){
            printf("%s\n",candidates[i].name);
            return true;
        }
}
    return false;
}

/**
 * @brief finds the minimum voted candidate 
 */
uint8_t find_min(void)
{
    uint8_t min=voter_count;
    for(uint8_t j=0;j<candidate_count;j++){
        if(candidates[j].eliminated==false &&candidates[j].votes<min){
            min=candidates[j].votes;
        }
    }
    return min;
}

/**
 * @brief checks if the election is tied
 */
bool is_tie(uint8_t min)
{
    for(uint8_t i=0;i<candidate_count;i++){
        if(!candidates[i].eliminated){
            if(candidates[i].votes>min)
            return false;
    }
}
return true;
}

/**
 * @brief eleminates the candidate that is in the last place 
 */
void eliminate(uint8_t min)
{
    for(uint8_t i=0;i<candidate_count;i++){
        if(candidates[i].votes==min){
            candidates[i].eliminated= true;
        }
    }
}
