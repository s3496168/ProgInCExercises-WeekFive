#include <stdio.h>
#include <stdlib.h>

#define NUM_ARGS 1
#define REQ_ARGS 2
#define HERE 0
#define FORWARDS 1

FILE * open_file(const char * fname){
    FILE * reader;
    reader = fopen(fname, "r");
    if(!reader){
        perror("fopen");
    }
    return reader;

}


int main (int argc, char * argv[]){
        FILE * reader;
        long filesize;

        /*if the required arguments are not present, it suggests there aren't the parameters for file opening
        and thus an error message should be returned*/
        if(argc != REQ_ARGS){
            fprintf(stderr, "ERROR! Please put in the name of a file to open\n");
            return EXIT_FAILURE;
        }

        /*open the file*/
        reader=open_file(argv[NUM_ARGS]);

        /*send an error message if the file is not opened*/
        if(!reader){
            return EXIT_FAILURE;
        }

        fseek(reader, HERE, SEEK_END);
        filesize = ftell(reader);
        fseek(reader, HERE, SEEK_SET);
        fprintf(stdout, "The size is: %ld bytes\n", filesize);

        /*close the file*/
        fclose(reader);
    return EXIT_SUCCESS;
}