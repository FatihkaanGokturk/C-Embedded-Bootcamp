#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

#define buffer_size 512
#define filename_length 8

static inline is_jpeg_header(const uint8_t *buffer){
    return (buffer[0]==0xff &&
            buffer[1]==0xd8 &&
            buffer[2]==0xff &&
            (buffer[3]&0xf0)==0xe0);
}

int main(int argc , char *argv[]){
    if(argc!=2){
        fprintf(stderr,"usage: ./recoverrewrite filename");
        return 1;
    }
    FILE *raw_file=fopen(argv[1],"r");
    if(raw_file==NULL){
        fprintf(stderr,"Error:Hardware fault couldn't read the file %s\n",argv[1]);
        return 1;
    }
    char filename[filename_length];
    bool on_file=false;
    uint8_t buffer[buffer_size];
    uint32_t file_counter=0;
    FILE *img_ptr=NULL;
    while(fread(buffer,sizeof(uint8_t),buffer_size,raw_file)==buffer_size) {
        if(is_jpeg_header(buffer)){
            if(on_file){
                fclose(img_ptr);
            }
        sprintf(filename,"%03u.jpg",file_counter);
        img_ptr=fopen(filename,"w");
        if(img_ptr==NULL){
            fprintf(stderr, "Error: File system write failure.\n");
            fclose(raw_file);
            return 1;
        }
        fwrite(buffer,sizeof(uint8_t),buffer_size,img_ptr);
        file_counter++;
        on_file=true;
        }
        else if(on_file){
            fwrite(buffer,sizeof(uint8_t),buffer_size,img_ptr);
        }

    }
    fclose(raw_file);
    if(on_file)
        fclose(img_ptr);
    return 0;
}