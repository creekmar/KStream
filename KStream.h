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

typedef struct stream *kstreamADT;

kstreamADT ks_create(FILE *input);
kstreamADT ks_destroy(kstreamADT);
kstreamADT ks_translate(kstreamADT);

