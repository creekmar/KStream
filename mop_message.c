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

#define _DEFAULT_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "KStream.h"

/// getinput         reads in the text from the input file
/// @param infile    the name of the input file to read
/// @return          the string read in
char * getinput(FILE * fp) {
    char output[2000] = "";
    char tmp;
    size_t counter = 0;

    //reading in 1999 bytes from file
    while(!feof(fp) && (strlen(output) != 1999)) {
        tmp = getc(fp);
        output[counter] = tmp;
        counter++;
    }

    //copying 1999 bytes with null terminator to a dynamic pointer
    char * out = (char *)malloc(strlen(output));
    if(out == NULL) {
        return NULL;
    }
    strncpy(out, output, strlen(output)-1);
    out[strlen(output)-1] = '\0';
    printf("output: %s\n", out);
    
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
    if(fp == NULL) {
        fprintf(stderr, "File could not be opened\n");
        return EXIT_FAILURE;
    }
    char * output;
    
    //continuously write translated file input into the output file
    while(!feof(fp)) {
        char * input = getinput(fp);
        printf("Output: %s\n", input);
        assert(input != NULL);
        output = ks_translate(stream, strlen(input) + 1, input);
        assert(output != NULL);
        if(outfile != stdout) {
            fwrite(output, strlen(output), 1, outfile);
        }
        else {
            for(int i = 0; i < (strlen(output)+1); i++) {
               if(isascii(output[i])) {
                   printf("%c", output[i]);
               }
               else {
                   printf("%x", output[i]);
               }
            }
            printf("\n");
        }
        free(input);
        free(output);
    }

    //closing files and freeing kstream
    if(outfile != stdout) {
        fclose(outfile);
    }
    fclose(fp);
    ks_destroy(stream);

}
