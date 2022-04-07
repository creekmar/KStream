//
// File: KStream.h
// KStream.h is an interface of an ADT that will encrypt and decode 
// text based on a given key
//
// @author: Ming Creekmore mec5765
//
// @date: 3/31/2022
//
// // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef _KSTREAM_H_
#define _KSTREAM_H_

#include <stdlib.h>

typedef struct kstream *kstreamADT;

/// ks_create function: creates a new kstreamADT instance
/// @param file         the name of the file with the key in it
/// @return             a new kstreamADT
kstreamADT ks_create(char *file);

void ks_destroy(kstreamADT box);
char * ks_translate(kstreamADT box, size_t len, char *input);
#endif
