// 
// File: KStream.c
// KStream.c implements the interface KStream.h
//
// @author Ming Creekmore mec5765
//
// @date: 3/31/2022
//
// // // // // // // // // // // // // // // // // // // // //

typedef struct stream {
    unsigned char *key;
    unsigned long keylen;
    unsigned char s[256];
    unsigned int i;
    unsigned int j;
} *kstreamADT;

kstreamADT ks_create(FILE *input) {

}

kstreamADT ks_destroy(kstreamADT) {

}

kstreamADT ks_translate(kstreamADT) {

}
