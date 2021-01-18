/*print charzacter by character*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define REQ_ARGS 2
#define NUM_ARGS 1

FILE* open_file(const char* fname) {
    FILE* reader;
    
    reader = fopen(fname, "r");
    if (!reader) {
        perror("fopen");
    }
    return reader;
}

char write(FILE* reader){
    char c;
    c =fgetc(reader);
      while (c != EOF) {
            printf("%c", c);
            c = fgetc(reader);
        }
        return c;
}

int main(int argc, char* argv[]) {
    FILE* reader;
    char c;

    /*detect if an appropriate filename exists*/
    if (REQ_ARGS != argc) {
        fprintf(stderr, "Error: please enter a filename! \n");
        return EXIT_FAILURE;
    }

    reader = open_file(argv[NUM_ARGS]);

    if (!reader) {
        return EXIT_FAILURE;
    }

    c=write(reader);
    if(!c){
        fprintf(stderr,"Error: the file has not been passed from main to the function \n");
    }
        fclose(reader);
    return EXIT_SUCCESS;
}
