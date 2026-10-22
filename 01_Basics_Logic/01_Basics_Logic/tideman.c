/**
 * @file tideman.c
 * @author Fatih Kaan GÖKTÜRK
 * @date 2026-03-13
 * @brief Implementation of the Tideman (Ranked Pairs) voting algorithm.
 * * This program simulates a ranked-choice election using the Tideman method. 
 * It tallies votes, determines the strength of victory between pairs of candidates, 
 * sorts them, and dynamically locks them into a directed graph (adjacency matrix). 
 * It features a recursive Depth-First Search (DFS) to prevent cyclical locks, 
 * ensuring a definitive winner (the source of the graph) can always be found.
 */


#include <stdio.h>
#include<stdbool.h>
#include<string.h>
#include <stdint.h>

// Max number of candidates
#define MAX 9
#define MAXLEN 100

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

uint8_t pair_count;
uint8_t candidate_count;

/**
 * @brief Updates the voter's ranks array given a new valid vote.
 * * @param rank The current preference level being voted on (0 is first choice).
 * @param name The string representing the candidate's name.
 * @param ranks The integer array tracking the voter's preferences.
 * @return true if the candidate's name is valid and recorded successfully.
 * @return false if the candidate's name does not match any valid candidate.
 */
bool vote(uint8_t rank, char *name, uint8_t ranks[]);
void record_preferences(uint8_t ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_cycle(uint8_t current_candidate, uint8_t target_candidate);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (uint8_t i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (uint8_t i = 0; i < candidate_count; i++)
    {
        for (uint8_t j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    uint8_t voter_count;
    printf("Number of voters: ");
    scanf("%hhu",&voter_count);

    // Query for votes
    for (uint8_t i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        uint8_t ranks[candidate_count];

        // Query for each rank
        for (uint8_t j = 0; j < candidate_count; j++)
        {
            char name[MAXLEN];
            printf("Rank %i: \n", j + 1);
            scanf("%s",name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            } 
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(uint8_t rank, char *name, uint8_t ranks[])
{
    for(uint8_t i=0;i<candidate_count;i++){
        if(strcmp(candidates[i],name)==0){
            ranks[rank]=i;
            return true;
        }
    }
    return false;
}

/**
 * @brief Updates the global preferences matrix given one voter's completed ranks.
 * * Iterates through the voter's rank array and increments the preferences matrix
 * to reflect that the candidate at rank 'i' is preferred over the candidate at rank 'j'.
 * * @param ranks The array representing a single voter's ranked preferences.
 */
void record_preferences(uint8_t ranks[])
{
    for(uint8_t i=0;i<candidate_count-1;i++){
        for(uint8_t j=i+1;j<candidate_count;j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

/**
 * @brief Records pairs of candidates where one is strictly preferred over the other.
 * * Scans the preferences matrix to find definitive winners between any two candidates.
 * Populates the global pairs array and updates the pair_count. Ties are ignored.
 */
void add_pairs(void)
{
    for(uint8_t i=0;i<candidate_count;i++){
        for(uint8_t j=0;j<candidate_count;j++){
            if(preferences[i][j]>preferences[j][i]){
                pairs[pair_count].winner=i;
                pairs[pair_count].loser=j;
                pair_count++;
            }
        }
    }
    return;
}

/**
 * @brief Sorts the pairs array in decreasing order by strength of victory.
 * * Utilizes a Bubble Sort algorithm to order the matchups. The strength of victory
 * is determined by checking the preferences matrix to see how many voters preferred 
 * the winner over the loser.
 */
void sort_pairs(void)
{
    pair temp;
    for(uint8_t j=0;j<pair_count;j++){
    for(uint8_t i=0;i<pair_count-1;i++){
        if(preferences[pairs[i+1].winner][pairs[i+1].loser]>preferences[pairs[i].winner][pairs[i].loser]){
            temp=pairs[i];
            pairs[i]=pairs[i+1];
            pairs[i+1]=temp;
        }
    }
    
}
return;
}
/**
 * @brief Locks pairs into the candidate graph in order, without creating cycles.
 * * Iterates through the sorted pairs and attempts to draw a directed edge (arrow) 
 * from the winner to the loser in the 'locked' adjacency matrix. It calls a 
 * recursive cycle-detection function to ensure the new edge does not create a closed loop.
 */
void lock_pairs(void)
{
    for(uint8_t i=0; i<pair_count;i++){
        if(is_cycle(pairs[i].loser,pairs[i].winner)==false){
            locked[pairs[i].winner][pairs[i].loser]=true;
        }
    }
    
    return;
}

/**
 * @brief Prints the winner of the election.
 * * Scans the 'locked' graph matrix to find the source node. A source node in the 
 * Tideman graph is defined as a candidate who has arrows pointing away from them, 
 * but zero arrows pointing at them (an in-degree of 0).
 */
void print_winner(void)
{
    for(uint8_t i=0;i<candidate_count;i++){
        bool is_winner=true;
        for(uint8_t j=0;j<candidate_count;j++){
            if(locked[j][i]==true){
                is_winner=false;
                break;
        }
        }
        if(is_winner==true)

            printf("%s\n",locked[i]);

            printf("%s\n",candidates[i]);
            return;

            printf("%s\n",candidates[i]);
            return;

    }

    return;
}

/**
 * @brief Recursive Depth-First Search (DFS) to detect cycles in the graph.
 * * Acts as a scout to trace pathways through the locked matrix. It starts at the 
 * loser of a potential pair and attempts to find any existing path back to the winner.
 * * @param current_candidate The node currently being investigated by the search.
 * @param target_candidate The original winner we are checking a path against.
 * @return true if a path exists from the current_candidate back to the target_candidate.
 * @return false if the search hits a dead end (no cycle found)..
 */

bool is_cycle(uint8_t current_candidate, uint8_t target_candidate ){
     if(current_candidate==target_candidate)
        return true;
    for(uint8_t i=0;i<candidate_count;i++){
        if(locked[current_candidate][i]==true){
            if (is_cycle(i,target_candidate)==true)
                return true;
        }
    }   
    return false;
    }