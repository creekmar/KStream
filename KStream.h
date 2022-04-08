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

/// ks_destroy function: destroys a kstreamADT instance
/// @box                 the kstream instance
void ks_destroy(kstreamADT box);

/// ks_translate function: translates given text to either encrypted or decrypted text depending on what was given
/// @param box           the kstream instance
/// @param len           the size of the input string
/// @param input         pointer to array of chats
/// @return              the translated text
char * ks_translate(kstreamADT box, size_t len, char *input);
#endif
