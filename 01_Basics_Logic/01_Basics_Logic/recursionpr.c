#include <stdio.h>
#include <stdbool.h>

// 10 boxes, 10 possible items inside each box.
// contents[current_box][inside_box] = 1 means 'inside_box' is inside 'current_box'
int contents[10][10];

// The Recursive Helper Function
bool search_box(int current_box, int target_key)
{
    // ---------------------------------------------------------
    // BASE CASE 1: The Brick Wall (Success)
    // ---------------------------------------------------------
    // If the box I am currently holding IS the target key, stop!
    if (current_box == target_key)
    {
        printf(">>> SUCCESS: Box %i IS the target key!\n", current_box);
        return true;
    }

    // ---------------------------------------------------------
    // THE RECURSIVE STEP: The Leap (The 'for' loop)
    // ---------------------------------------------------------
    // I haven't found it yet. Look at all 10 slots inside my current box.
    for (int i = 0; i < 10; i++)
    {
        // Is there actually a smaller box in this slot?
        if (contents[current_box][i] == 1)
        {
            printf("Standing in Box %i, found Box %i inside. Opening it...\n", current_box, i);
            
            // THE PAUSE & CALL: 
            // The loop in current_box freezes. We dive into Box 'i'.
            if (search_box(i, target_key) == true)
            {
                // If the dive eventually found the key, pass the 'true' back up!
                return true; 
            }
        }
    }

    // ---------------------------------------------------------
    // BASE CASE 2: The Brick Wall (Failure / Dead End)
    // ---------------------------------------------------------
    // The loop finished. I checked all 10 slots in this box. No key.
    printf("<<< DEAD END: Box %i is empty. Going back.\n", current_box);
    return false;
}

int main(void)
{
    // Setup: Empty all boxes first (Fill with 0s)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            contents[i][j] = 0;
        }
    }

    // Build the maze (This is identical to drawing arrows on your Tideman graph)
    // Box 0 contains two boxes: Box 1 and Box 2.
    contents[0][1] = 1; 
    contents[0][2] = 1; 
    
    // Box 1 is a dead end. It contains nothing.
    
    // Box 2 contains Box 5.
    contents[2][5] = 1; 
    
    // We are looking for Box 5. We start searching from Box 0.
    int starting_box = 0;
    int target = 5;

    printf("MISSION: Start at Box %i, find Target %i\n\n", starting_box, target);

    // Launch the robot!
    if (search_box(starting_box, target) == true)
    {
        printf("\nRESULT: A path to the key exists!\n");
    }
    else
    {
        printf("\nRESULT: Impossible to reach the key from here.\n");
    }

    return 0;
}