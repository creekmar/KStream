// 
// File: KStream.c
// KStream.c implements the interface KStream.h
//
// @author Ming Creekmore mec5765
//
// @date: 3/31/2022
//
// // // // // // // // // // // // // // // // // // // // //

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "KStream.h"
#define index1 box->i
#define index2 box->j
#define stream box->s

/// struct kstream: struct to hold kstream values
/// key             array of chars for the key
/// keylen          the length of key in bytes
/// s               stream table of random bytes for encryption
/// i               the first index
/// j               the second index
struct kstream {
    unsigned char key[8];
    unsigned long keylen;
    unsigned char s[256];
    unsigned int i;
    unsigned int j;
};

/// next_byte returns the next encrypted byte
/// @return    the next byte
static char next_byte(kstreamADT box) {
    box->i = (box->i+1) % 256;
    box->j = (box->j + stream[box->i]) % 256;
    char tmp = stream[box->i];
    stream[box->i] = stream[box->j];
    stream[box->j] = tmp;
    tmp = stream[(stream[box->i] + stream[box->j]) % 256];
    return tmp;
}

/// ks_create creates a new kstreamADT
kstreamADT ks_create(char *file) {
    //get key
    FILE *fp = fopen(file, "r");
    kstreamADT box = (kstreamADT)malloc(sizeof(struct kstream));
    fread(box->key, sizeof(long), 1, fp);
    box->keylen = 8;
    
    //initialize the stream
    for(box->i = 0; box->i < 256; box->i++) {
        stream[box->i] = box->i;
    }

    //randomize elements by swapping different indexes
    box->j = 0;
    for(box->i = 0; box->i < 256; box->i++) {
        box->j = (box->j + stream[box->i] + box->key[box->i % box->keylen]) % 256;
        unsigned char tmp = stream[box->i];
        stream[box->i] = stream[box->j];
        stream[box->j] = tmp;
    }
    //skip first 1024 bytes of KStream to prime system
    for(int i = 0; i < 1025; i++) {
        next_byte(box);
    }

    fclose(fp);
    return box;
}

void ks_destroy(kstreamADT box) {
    free(box);
}

char * ks_translate(kstreamADT box, size_t len, char *input) {
    if(len == 0) {
        return "";
    }
    char * output = (char *)malloc(len+1);
    output[0] = '\0';
    for(size_t i = 0; i < len - 1; i++) {
        char tmp = input[i] ^ next_byte(box);
        strncat(output, &tmp, 1);
    }
    //char tmp = '\0';
    //strncat(output, &tmp, 1);
    return output;
}
