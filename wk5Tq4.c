#include <stdlib.h>
#include <stdio.h>

#define REQ_ARGS 2
#define NUM_ARGS 1
#define TOTAL 100

/*Boolean to enable the functio to be used*/
typedef enum {
    FALSE,
    TRUE
} BOOLEAN;

/*Function to read the file*/
FILE *read_file(const char *fname) {
    FILE *reader;
    reader = fopen(fname, "r");
    if (!reader) {
        perror("fopen");
    }
    return reader;
}

/*Function to write to the file-just in case*/
FILE *write_file(const char *fname) {
    FILE *writer;
    writer = fopen(fname, "w");
    if (!writer) {
        perror("fopen");
    }
    return writer;
}

/*attempt at passing data stream to be processed
note size_t is an unsigned data type*/
BOOLEAN read_binary_integer(int *value, FILE *stream) {
    size_t nelts;
    /*fread can read the data from an incoming file into an array*/
    if (fread(&nelts, sizeof(size_t), 1, stream) != 1 ||
        fread(&value, sizeof(value), nelts, stream) != nelts) {
        perror("Failed to read data");
        return FALSE;
    }
    return TRUE;
}

int main(int argc, char *argv[]) {
    FILE *reader;
    BOOLEAN read;
    /*array large enough for the small incoming stram*/
    int stream[TOTAL];

    if (argc != REQ_ARGS) {
        fprintf(stderr, "Error! Please enter a file to open!\n");
        return EXIT_FAILURE;
    }

    /*open the file*/
    reader = read_file(argv[NUM_ARGS]);

    /*if the file cannot be opened exit gracefully*/
    if (!reader) {
        return EXIT_FAILURE;
    }

    /*pass in the file to be processed*/
    read = read_binary_integer(stream, reader);

    /*Additional error to remind user that the data could not be processed*/
    if (!read) {
        fprintf(stderr,
                "Sorry! The file was bought in successfully but could not be "
                "processed\n");
    }

    /*close the file*/
    fclose(reader);

    return EXIT_SUCCESS;
}
