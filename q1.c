#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*ctype.h permits use of space after number*/
#include <ctype.h>
/*auto definition of min and max values*/
#include <limits.h>

#define DELIM ","
#define MAXNUMS 10
#define LINELEN 80
#define EXTRACHARS 2
#define DECIMAL 10
#define FILEARG 1
#define REQUIRED_ARGS 2

typedef enum {
    FALSE,
    TRUE
} BOOLEAN;

FILE* open_file(const char* fname) {
    FILE* reader;

    reader = fopen(fname, "r");
    if (!reader) {
        perror("fopen");
    }
    return reader;
}

/*private function to convert string to integer*/
static BOOLEAN strtoint(const char string[], int* result) {
    /*note that end points at the the last non numeric
     * character successfully parsed-for an int this would be the newline
     * character*/
    char* end;
    long value;

    value = strtol(string, &end, DECIMAL);

    while (isspace(*end)) {
        /*allows for the moving forward of one character*/
        ++end;
    }
    /*detect non zero value (non numeric data*/
    if (*end) {
        fprintf(stderr, "Error: non-numeric data in the file.\n");
        return FALSE;
    }
    if (value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "Error: number outside the range of an int!\n");
        return FALSE;
    }
    *result = (int)value;
    return TRUE;
}

/*read in the array of numbers*/
BOOLEAN read_nums(FILE* reader, int* array, int* numbercount) {
    int count = 0;
    char inputLine[LINELEN + EXTRACHARS];
    char* tok;

    assert(reader != NULL);

    /*note that reader is the file input*/
    if (fgets(inputLine, LINELEN + EXTRACHARS, reader) == NULL) {
        return FALSE;
    }
    if (inputLine[strlen(inputLine) - 1] != '\n') {
        /*note perror not used as the error is not system generated*/
        fprintf(stderr, "Error: buffer overflow!\n");
        return FALSE;
    }
    tok = strtok(inputLine, DELIM);
    /*keep going while there are tokens*/
    do {
        int num;
        /*return an error if there are too many*/
        if (count >= MAXNUMS) {
            fprintf(stderr, "Error: too many numbers in the file \n");
            return FALSE;
        }
        /*trigger an error message by returning false if tokenisation did
         * not happen*/
        if (!strtoint(tok, &num)) {
            return FALSE;
        }
        array[count++] = num;
        tok = strtok(NULL, DELIM);
    } while (tok);
    *numbercount = count;
    return TRUE;
}

/*add the numbers-note that count does not need to be used elsewhere so
 * count is not a pointer*/
int sum_nums(const int* array, int array_count) {
    int sum = 0;
    int count;
    for (count = 0; count < array_count; ++count) {
        sum += array[count];
    }
    return sum;
}

/*write the numbers out*/
BOOLEAN write_nums(const char* fname, const int* array, int numbercount,
                   int sum) {
    FILE* writer;
    int count;
    writer = fopen(fname, "w");
    if (!writer) {
        /*custom error message*/
        perror("fopen in write_nums");
        return FALSE;
    }

    for (count = 0; count < numbercount; ++count) {
        fprintf(writer, "%d,", array[count]);
    }
    fprintf(writer, "%d\n", sum);
    fclose(writer);
    return TRUE;
}

int main(int argc, char* argv[]) {
    /*
    int numbers[MAXNUMS];
    return
    */
    int numarray[MAXNUMS];
    int arraylen;
    int total;
    FILE* reader;

    if (REQUIRED_ARGS != argc) {
        fprintf(stderr,
                "Error: invalid args provided, You should provide a filename "
                "for me to open!\n");
        return EXIT_FAILURE;
    }

    reader = open_file(argv[FILEARG]);

    if (!reader) {
        return EXIT_FAILURE;
    }
    if (!read_nums(reader, numarray, &arraylen)) {
        /*close the file*/
        fclose(reader);
        return EXIT_FAILURE;
    }
    total = sum_nums(numarray, arraylen);
    if (!write_nums(argv[FILEARG], numarray, arraylen, total)) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
