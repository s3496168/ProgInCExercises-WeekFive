#include <stdio.h>
#include <stdlib.h>
#include "fsupport.h"
#include "phone.h"

int load(struct phone_entry*, FILE*);
BOOLEAN save(struct phone_entry*, size_t num_entries, FILE*);
void print_book(struct phone_entry*, int);
typedef enum { FNAME, LNAME, NUMBER } token_number;
#define NUMTOKENS 3

int main(int argc, char** argv)
{
    FILE *fpRead;
    FILE * out;
    struct phone_entry list[DIRECTORYSIZE];
    int result;

    /* zero out the array so it is fully initialised */
    memset(list,  0, sizeof(struct phone_entry) * DIRECTORYSIZE);

    /* check for the correct number of command line arguments */
    if(argc != 2)
    {
        fprintf(stderr, "Error: invalid arguments.\n\n");
        return EXIT_FAILURE;
    }
    /* open the input file */
    fpRead = gropen(argv[1]);
    /* load the data and handle errors */
    result = load(list, fpRead);
    fclose(fpRead);
    if(result <= 0)
    {
        fprintf(stderr, "Error: failed to load data.\n\n");
        return EXIT_FAILURE;
    }
    /* print out the data */
    print_book(list, result);
    /* open a binary file to write the data to */
    out=gwopen("output.bin");
    if(!save(list, result, out))
    {
        fprintf(stderr, "Error: I/O Error occured.\n\n");
        return EXIT_FAILURE;
    }
    /* whatever we open we must close */
    fclose(out);
    return EXIT_SUCCESS;
}

/***************************************************************************
* load data in from disk. 
***************************************************************************/
int load(struct phone_entry* entries, FILE* fpRead)
{
    char line[MAXWIDTH+EXTRASPACES];
    unsigned entrycount=0;
    /* read in each line from the file, ensuring there is space to store 
     * it */
    while(fgets(line, MAXWIDTH+EXTRASPACES, fpRead) != NULL &&
        entrycount < DIRECTORYSIZE)
    {
        char fname[NAMELEN+1], lname[NAMELEN+1], number[PHONELEN+1];
        char linecpy[MAXWIDTH+EXTRASPACES];
        char * token;
        /* keep a count of the current token */
        token_number curtoken=0;

        /* remove the newline from the line read in so it does not get 
         * stored in the last token 
         */
        line[strlen(line)-1]=0;
        /* make a copy of the line in case we need to use in in error 
         * messages
         */
        memcpy(linecpy, line, MAXWIDTH+EXTRASPACES);

        /* start string tokenization */
        token = strtok(line, ",");
        while(token)
        {
            /* check which token we are up to and copy the data into the 
             * appropriate string
             */
            switch(curtoken)
            {
                case FNAME:
                    strcpy(fname, token);
                    break;
                case LNAME:
                    strcpy(lname, token);
                    break;
                case NUMBER:
                    strcpy(number, token);
                    break;
                default:
                    /* if there are too many tokens, display an error */
                    fprintf(stderr, "invalid line in file: %s\n", linecpy);
                    return EOF;
            }
            /* get the next token */
            token = strtok(NULL, ",");
            ++curtoken;
        }
        /* insert the data into the array */
        strcpy(entries[entrycount].fname, fname);
        strcpy(entries[entrycount].lname, lname);
        strcpy(entries[entrycount].number, number);
        ++entrycount;
    }
    return (int)entrycount;
}

/**************************************************************************
 * save() - save data from the phonebook into a file in binary format. 
 * The assumption we are making here is that the outstream FILE pointer 
 * points to a valid open file we can write to.
 *************************************************************************/
BOOLEAN save(struct phone_entry* phone_book, size_t num_entries, 
    FILE*outstream)
{

    /* write the data in the phone_book array to a file all at once */
    if(fwrite(&num_entries, sizeof(size_t), 1, outstream) !=  1
        ||     fwrite(phone_book, sizeof(struct phone_entry), 
                num_entries, outstream) != num_entries)
    {
        perror("failed to save data");
        return FALSE;
    }
    return TRUE;
}

/***************************************************************************
* print out the data in the phone book.
***************************************************************************/
void print_book(struct phone_entry* entries, int num_entries)
{
    unsigned count; 
    /* document our assumption that the array has already been 
     * processed already
     */
    assert(num_entries > 0);
    /* print out each entry */
    for(count = 0; count < (unsigned)num_entries; ++count)
    {
        printf("%s\t%s\t%s\n", entries[count].fname, entries[count].lname,
            entries[count].number);
    }
}
