#include <stdio.h>
#include <stdlib.h>

#define NUM_ARGS 1
#define REQ_ARGS 2

FILE* open_file(const char* fname) {
    FILE* reader;
    reader = fopen(fname, "rb");
    if (!reader) {
        perror("fname");
    }
    return reader;
}

char place(FILE* reader) {
    char c;
    c = fgetc(reader);
    while (c != EOF) {
        printf("%c", c);
        c = fgetc(reader);
    }
    printf("\n");
    return c;
}

int main(int argc, char* argv[]) {
    FILE* reader;
    char c;

    if (argc != REQ_ARGS) {
        fprintf(stderr, "Error! Please enter a file to open!\n");
        return EXIT_FAILURE;
    }

    reader = open_file(argv[NUM_ARGS]);

    if (!reader) {
        return EXIT_FAILURE;
    }

    c = place(reader);

    if (!c) {
        fprintf(stderr, "Error: the file could not be processed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
