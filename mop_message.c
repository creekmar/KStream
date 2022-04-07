//
// File: mop_message.c
// mop_message.c is a program that will encrypt or decrypt a message
// given a keyfile, an input text file, and a specified output file
//
// @author Ming Creekmore mec5765
//
// @date 3/31/2022
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KStream.h"

/// getinput         reads in the text from the input file
/// @param infile    the name of the input file to read
/// @return          the string read in
char * getinput(char * infile) {
    FILE * fp = fopen(infile, "r");
    char output[2000];
    char tmp;
    while((tmp = getc(fp)) != EOF) {
        strncat(output, &tmp, 1);
    }

    //copy input to a char pointer that can be moved (heap)
    size_t actual_len = strlen(output)-2;
    char * out = (char *)malloc(actual_len);
    strncpy(out, output+1, actual_len);

    return out;
}

int main(int argc, char*argv[]) {

    //check if using it correctly
    if(argc != 4) {
        fprintf(stderr, "Usage: mop_message keyfile in-file [ out-file | - ]\n");
        return EXIT_FAILURE;
    }
    
    //initialize stuff
    kstreamADT stream = ks_create(argv[1]);
    char * input = getinput(argv[2]);
    char * output;
    output = ks_translate(stream, strlen(input), input);

    if(strncmp(argv[3], "-", 1) == 0) {
        printf("%s\n", output);
    }
    else {
        FILE * outfile = fopen(argv[3], "w");
        fwrite(output, strlen(input), 1, outfile);
    }
    printf("Done\n");
    
    free(output);
    ks_destroy(stream);

}
