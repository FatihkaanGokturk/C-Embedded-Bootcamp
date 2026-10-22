#include <stdbool.h>
#include <stdint.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// 8-bit unsigned integers save 75% memory compared to standard 'int'
uint8_t preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    const char *name; // 'const' forces string into Flash memory
    uint8_t votes;    // 0-255 is plenty for 100 voters
    bool eliminated;  
} Candidate_t;

Candidate_t candidates[MAX_CANDIDATES];
uint8_t voter_count;
uint8_t candidate_count;

// Notice how fast Tabulate becomes when it's just pure 8-bit math
void tabulate(void)
{   
    for (uint8_t i = 0; i < voter_count; i++) {
        for (uint8_t j = 0; j < candidate_count; j++) {
             if (!candidates[preferences[i][j]].eliminated) {
                candidates[preferences[i][j]].votes++;
                break;
             }
        }
    }
}

// Bitwise right-shift (voter_count >> 1) is a faster way to divide by 2 on ARM processors
bool print_winner(void)
{   
    uint8_t threshold = voter_count >> 1; 
    
    for (uint8_t i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes > threshold) {
            // In embedded, you'd trigger a UART TX interrupt here instead of printf
            return true;
        }
    }
    return false;
}

uint8_t find_min(void)
{
    uint8_t min = voter_count;
    for (uint8_t j = 0; j < candidate_count; j++) {
        if (!candidates[j].eliminated && candidates[j].votes < min) {
            min = candidates[j].votes;
        }
    }
    return min;
}