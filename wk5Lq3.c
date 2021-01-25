#include <stdlib.h>
#include <stdio.h>

#define REQ_ARGS 4
#define FIRST_ARGS 1
#define SECOND_ARGS 2
#define THIRD_ARGS 3

FILE* read_file(const char* fname) {
    FILE* reader;
    reader = fopen(fname, "r");
    if (!reader) {
        perror("fopen");
    }
    return reader;
}

FILE* write_file(const char* fname) {
    FILE* writer;
    writer = fopen(fname, "w");
    if (!writer) {
        perror("fopen");
    }
    return writer;
}

char place_things(FILE* reader, FILE* writer) {
    char c;
    c = fgetc(reader);
    while (c != EOF) {
        fputc(c, writer);
        c = fgetc(reader);
    }

    return c;
}

int main(int argc, char* argv[]) {
    FILE* readerOne;
    FILE* readerTwo;
    FILE* writer;
    char c;
    char d;

    /*if files cannot be found*/
    if (argc != REQ_ARGS) {
        fprintf(stderr,
                "Error! Please enter the names of two files for reading and "
                "one for output!\n");
        return EXIT_FAILURE;
    }

    readerOne = read_file(argv[FIRST_ARGS]);
    readerTwo = read_file(argv[SECOND_ARGS]);
    writer = write_file(argv[THIRD_ARGS]);

    /*error to deal with any missing files*/
    if (!readerOne || !readerTwo || !writer) {

        return EXIT_FAILURE;
    }

    c = place_things(readerOne, writer);
    d = place_things(readerTwo, writer);

    if (!c || !d) {
        fprintf(stderr, "Error: files cannot be written out!\n");
        return EXIT_FAILURE;
    }

    printf("All files merged.\n");

    fclose(readerOne);
    fclose(readerTwo);
    fclose(writer);

    return EXIT_SUCCESS;
}
