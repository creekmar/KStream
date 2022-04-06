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
#include <KStreamADT.h>

int main(int argc, char*argv[]) {
    //make three files
    char *keyfile;
    char *infile;
    char *outfile;

    //check if using it correctly
    if(argc != 4) {
        fprintf(stderr, "Usage: mop_message keyfile in-file [ out-file | - ]\n");
        return EXIT_FAILURE;
    }
    
    //initialize file names based on arguments
    keyfile = argv[1];
    infile = argv[2];
    if(argv[3] == "-") {
        outfile = "stdout";
    }
    else {
        outfile = argv[3];
    }

    kstreamADT stream = ks_create(keyfile);
    

}
