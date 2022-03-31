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
    FILE *keyfile;
    FILE *infile;
    FILE *outfile;
    if(argc != 4) {
        fprintf(stderr, "Usage: mop_message keyfile in-file [ out-file | - ]\n");
        return EXIT_FAILURE;
    }

    keyfile = fopen(argv[1], "rb");
    infile = fopen(argv[2], "r");
    if(argv[3] == "-") {
        outfile = stdout;
    }
    else {
        outfile = fopen(argv[3], "wb");
    }

}
