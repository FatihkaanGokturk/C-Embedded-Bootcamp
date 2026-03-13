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

// Function prototypes
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

// Update preferences given one voter's ranks
void record_preferences(uint8_t ranks[])
{
    for(uint8_t i=0;i<candidate_count-1;i++){
        for(uint8_t j=i+1;j<candidate_count;j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
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

// Sort pairs in decreasing order by strength of victory
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
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(uint8_t i=0; i<pair_count;i++){
        if(is_cycle(pairs[i].loser,pairs[i].winner)==false){
            locked[pairs[i].winner][pairs[i].loser]=true;
        }
    }
    
    return;
}

// Print the winner of the election
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
<<<<<<< HEAD:01_Basics_Logic/tideman.c
            printf("%s\n",locked[i]);
=======
            printf("%s\n",candidates[i]);
            return;
>>>>>>> 3662cd2 (docs: add professional Doxygen documentation and memory optimizations):tideman.c
    }

    return;
}
<<<<<<< HEAD:01_Basics_Logic/tideman.c
=======
/**
 * @brief Recursive Depth-First Search (DFS) to detect cycles in the graph.
 * * Acts as a scout to trace pathways through the locked matrix. It starts at the 
 * loser of a potential pair and attempts to find any existing path back to the winner.
 * * @param current_candidate The node currently being investigated by the search.
 * @param target_candidate The original winner we are checking a path against.
 * @return true if a path exists from the current_candidate back to the target_candidate.
 * @return false if the search hits a dead end (no cycle found)..
 */
>>>>>>> 3662cd2 (docs: add professional Doxygen documentation and memory optimizations):tideman.c
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