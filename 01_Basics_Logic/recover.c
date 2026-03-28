#include <stdio.h>
#include <stdlib.h>
#include<stdint.h> 
/**
 * @file recover.c
 * @brief Recovery of JPEG files from a raw memory card.
 * @author Fatih Kaan GÖKTÜRK
 * @date 3/28/2026
 *
 * @details   Validates command-line arguments, manages the file pointers for 
 * both the reading of the raw block and the writing of the recovered 
 * images. Ensures no memory leaks occur by safely closing active 
 * pointers before opening new ones or exiting.
 *
 * @param[in] argc  Number of command-line arguments. Expected exactly 2.
 * @param[in] argv  Array of command-line arguments. argv[1] is the target raw file.
 *
 * @return    int   0 upon successful recovery, 1 on invalid usage or I/O failure.
 */


int main(int argc, char *argv[])
{
    // Validate command-line arguments
    if(argc!=2){
        printf("Usage: ./recover image\n");
        return 1;
    }
    char filename[8];
    int on_file=0;
    uint8_t buffer[512];
    uint8_t file_counter =0;
    // Open the forensic raw file
    FILE *raw_file=fopen(argv[1],"r");
    if(raw_file==NULL){
        printf("Couldn't open the file\n");
        return 1;
    }
    FILE *img= NULL;
    // Shovel 512-byte blocks until the end of the file is reached
    while(fread(buffer, 1, 512, raw_file)==512){
    // Check block for JPEG magic numbers using a bitwise mask
     if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0) == 0xe0){
        // If a previous JPEG is currently open, close it to prevent memory leaks
        if(on_file==1){
            fclose(img);
        }
        // Format the new filename and open the new file pointer
        sprintf(filename,"%03i.jpg",file_counter);
        img =fopen(filename,"w");    
        fwrite(buffer, 1, 512, img);
        file_counter ++;
        on_file=1;
        }
        // If no JPEG numbers, but we are currently tracking an active JPEG
        else if(on_file ==1){
            fwrite(buffer,1,512,img);
        }
        // Slack space (garbage data): do nothing and move to the next block
        else{

        }
    }
    // Safely clean up all active pointers before exiting
    fclose(raw_file);
    if (on_file==1){
        fclose(img);
    }
    return 0;
}       