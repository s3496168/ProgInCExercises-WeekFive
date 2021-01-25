#include <stdio.h>
#include <stdlib.h>

#define REQ_ARGS 2
#define NUM_ARGS 1
#define MAXNUMS 3

/*function for writing the required bin file*/
FILE* bin_file(float* binArray) {
    FILE* bin;
    /*int i;*/

    bin = fopen("numArray.bin", "wb");
    if (!bin) {
        perror("fopen");
    }

    /*This loop creates human readable data*/
    /*for(i=0; i<MAXNUMS; ++i){
        fprintf(bin,"%.2f\n", binArray[i]);

    }*/
    /*This writes non human readable binary data*/
    fwrite(binArray, sizeof(int), sizeof(binArray), bin);
    return bin;
}
/*end function for writing the required bin file*/

/*function for writing the required txt file*/
FILE* txt_file(float* txtArray) {
    FILE* txt;
    int i;

    txt = fopen("numArray.txt", "w");
    if (!txt) {
        perror("fopen");
    }
    /*This loop creates human readable data*/
    for (i = 0; i < MAXNUMS; ++i) {
        fprintf(txt, "%.2f\n", txtArray[i]);
    }
    /*This writes non human readable binary data*/
    /* fwrite(txtArray, sizeof(int), sizeof(txtArray), txt);*/
    return txt;
}
/* end function for creating the required txt array*/

/*this function takes the file name from main and then opens that file*/
FILE* open_file(const char* fname) {
    FILE* reader;
    /*first testing print statement*/
    printf("The name is %s\n", fname);
    reader = fopen(fname, "r");
    if (!reader) {
        perror("fopen");
    }
    return reader;
}
/*end this function takes the file name from main and then opens that file*/

/*This function opens the file listed internally*/
FILE* open_bin(void) {
    FILE* reader;
    /*first testing print statement*/
    reader = fopen("numArray.bin", "r");
    if (!reader) {
        perror("fopen");
    }

    return reader;
}
/*end fhis function opens the file listed internally*/

/*function to permit displaying iof file content*/
char display(FILE* reader) {
    char c;
    c = fgetc(reader);
    /*second testing print statement*/
    fprintf(stdout, "HI!\n");
    while (c != EOF) {
        printf("%c", c);
        c = fgetc(reader);
    }
    return c;
}
/*end function to permit displaying iof file content*/

int main() {

    FILE* writeBin;
    FILE* writeTxt;
    FILE* readBin;
    FILE* readTxt;
    FILE* testBin;
    char c;
    char d;
    char e;
    char* a = "numArray.bin";
    char* b = "numArray.txt";

    /*arrays for demonstration*/
    float binArray[MAXNUMS] = {1.1, 2.2, 3.3};
    float txtArray[MAXNUMS] = {1.1, 2.2, 3.3};

    /*write out function call ins*/
    writeBin = bin_file(binArray);
    writeTxt = txt_file(txtArray);

    /*error statements if the writeout cannot be initialised*/
    if (!writeBin || !writeTxt) {
        return EXIT_FAILURE;
    }

    /*printing statement to see if files to be opened are being read int*/
    printf("Name A %s\n", a);
    printf("Name B %s\n", b);

    /*attempt at opening created files*/
    readBin = open_file(a);
    readTxt = open_file(b);
    testBin = open_bin();

    /*if the (created) files cannot be read in, display an error*/
    if (!readBin || !readTxt) {
        fprintf(stderr, "Sorry, the files cannot be read \n");
        return EXIT_FAILURE;
    }

    /*display the created files*/
    c = display(readBin);
    d = display(readTxt);
    e = display(testBin);

    /*if the files cannot be displayed, display an error*/
    if (!c || !d || !e) {
        fprintf(stderr, "Sorry, the files cannot be displayed \n");
        return EXIT_FAILURE;
    }

    /*close the files*/
    fclose(readBin);
    fclose(readTxt);
    fclose(testBin);
    return EXIT_SUCCESS;
}
