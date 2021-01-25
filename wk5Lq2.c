#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_ARGS 1
#define REQ_ARGS 2

#define HERE 0
#define FORWARD 1
#define LINELEN 80
#define EXTRACHARS 2

#define DELIM " "

/*
number of lines
number of words
number of characters
*/

typedef enum {
    FALSE,
    TRUE
} BOOLEAN;

BOOLEAN loop = FALSE;

FILE* read_file(const char* fname) {
    FILE* reader;
    reader = fopen(fname, "r");
    if (!reader) {
        perror("fopen");
    }
    return reader;
}
/*internal only function to clear the buffer*/
static void read_rest_of_line(FILE* reader) {
    int ch;
    while (ch = getchar(), ch != EOF && ch != '\n') {
        ;
        clearerr(reader);
    }
}

/*function to read lines*/
char countLine(FILE* reader) {
    char c[LINELEN + EXTRACHARS];
    int b;
    b = 0;

    while (fgets(c, LINELEN + EXTRACHARS, reader)) {
        /*buffer overflow test and management*/
        if (c[strlen(c) - 1] != '\n') {
            /*A custom error is necessary as buffer overflow
            is a custom error*/
            printf("Error! Buffer overflow! \n");
            read_rest_of_line(reader);
            continue;
        }
        /*remove trailing newline*/
        c[strlen(c) - 1] = 0;

        /*itineration counter*/
        b += 1;

        /*kill the loop*/
        loop = TRUE;
    }

    return b;
}

int tokeniser(FILE* reader) {
    int token;
    char* tok;
    char c[LINELEN + EXTRACHARS];
    int b;
    token = 1;
    b = 0;

    while (fgets(c, LINELEN + EXTRACHARS, reader)) {
        /*buffer overflow test and management*/
        if (c[strlen(c) - 1] != '\n') {
            /*A custom error is necessary as buffer overflow
            is a custom error*/
            printf("Error! Buffer overflow! \n");
            read_rest_of_line(reader);
            continue;
        }
        /*remove trailing newline*/
        c[strlen(c) - 1] = 0;
        /*attempt to tokenise each line*/
        tok = strtok(c, DELIM);

        while (tok != NULL) {
            /*counter to itinerate waech time there is a token in the line*/
            ++token;
            tok = strtok(NULL, DELIM);
        }

        /*kill the loop*/
        loop = TRUE;
    }
    /*add the tokens identified in the line to the tokens identified in the
     * other lines*/
    b += token;

    return b;
}

int main(int argc, char* argv[]) {
    FILE* reader;
    long characters;
    int z;
    int t;

    if (argc != REQ_ARGS) {
        fprintf(stderr, "Error! Please enter a file name to open that file\n");
        return EXIT_FAILURE;
    }

    reader = read_file(argv[NUM_ARGS]);

    if (!reader) {
        return EXIT_SUCCESS;
    }

    /**fseek to get character numbers*/
    fseek(reader, HERE, SEEK_END);
    characters = ftell(reader);
    fseek(reader, HERE, SEEK_SET);
    z = countLine(reader);
    t = tokeniser(reader);
    if (!z) {
        fprintf(stderr, "Error, the line number could not be determined");
    }

    fprintf(stdout, "  %d  %d %ld %s\n", z, t, characters, argv[NUM_ARGS]);

    /*close the file*/
    fclose(reader);

    return EXIT_SUCCESS;
}
