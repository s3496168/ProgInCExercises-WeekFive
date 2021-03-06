/*print line by line*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define REQ_ARGS 2
#define NUM_ARGS 1
#define LINELEN 80
#define EXTRACHARS 2

typedef enum {
    FALSE,
    TRUE
} BOOLEAN;

BOOLEAN loop = FALSE;

FILE* open_file(const char* fname) {
    FILE* reader;

    reader = fopen(fname, "r");
    if (!reader) {
        perror("fopen");
    }
    return reader;
}

/*static as extenal visibility is not needed*/
static void read_rest_of_line(FILE* reader) {
    /*char to read from the buffer*/
    int ch;
    /*itinerate through the characters in the buffer to clear it*/
    while (ch = getchar(), ch != EOF && ch != '\n')
        ;
    clearerr(reader);
}

char write(FILE* reader) {
    char c[LINELEN + EXTRACHARS];
    char e;
    while (fgets(c, LINELEN + EXTRACHARS, reader)) {
        /*buffer overflow test and management*/
        if (c[strlen(c) - 1] != '\n') {
            /*error generated by program, not system
            so custom error message is necessary*/
            printf("Error, buffer overflow! \n");
            read_rest_of_line(reader);
            continue;
        }
        /*remove trailing newline*/
        c[strlen(c) - 1] = 0;
        puts(c);
        loop = TRUE;
    }

    if (loop != FALSE) {
        e = 1;
    }

    return e;
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

    c = write(reader);
    if (!c) {
        fprintf(
            stderr,
            "Error: the file has not been passed from main to the function \n");
    }
    fclose(reader);
    return EXIT_SUCCESS;
}
