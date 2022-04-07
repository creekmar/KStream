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
char * getinput(FILE * fp) {
    char output[2000] = "";
    char tmp;
    while(!feof(fp) && (strlen(output) != 1999)) {
        tmp = getc(fp);
        strncat(output, &tmp, 1);
    }

    char * out = (char *)malloc(strlen(output)-2);
    strncpy(out, output, strlen(output)-2);

    printf("Testing: %s\ndone\n", out);
    //copy input to a char pointer that can be moved (heap)
    //size_t actual_len = strlen(output)-1;
   // printf("length: %ld\nActual length: %ld\n", strlen(output), actual_len);
    
    return out;
}

int main(int argc, char*argv[]) {

    //check if using it correctly
    if(argc != 4) {
        fprintf(stderr, "Usage: mop_message keyfile in-file [ out-file | - ]\n");
        return EXIT_FAILURE;
    }
    
    //open outfile
    FILE * outfile;
    if(strncmp(argv[3], "-", 1) == 0) {
        outfile = stdout;
    }
    else {
        outfile = fopen(argv[3], "w");
    }

    //creating instances
    kstreamADT stream = ks_create(argv[1]);
    FILE * fp = fopen(argv[2], "r");
    char * output;
    
    //continuously write translated file input into the output file
    while(!feof(fp)) {
        char * input = getinput(fp);
        output = ks_translate(stream, strlen(input)+1, input);
        fwrite(output, strlen(output)+1, 1, outfile);
        free(output);
    }

    if(outfile != stdout) {
        fclose(outfile);
    }

    printf("Done\n");
   
    ks_destroy(stream);

}
