// 
// File: KStream.c
// KStream.c implements the interface KStream.h
//
// @author Ming Creekmore mec5765
//
// @date: 3/31/2022
//
// // // // // // // // // // // // // // // // // // // // //

#define index1 box->i
#define index2 box->j
#define stream box->s

/// struct kstream: struct to hold kstream values
/// key             array of chars for the key
/// keylen          the length of key in bytes
/// s               stream table of random bytes for encryption
/// i               the first index
/// j               the second index
typedef struct kstream {
    unsigned char key[8];
    unsigned long keylen;
    unsigned char s[256];
    unsigned int i;
    unsigned int j;
} *kstreamADT;

/// next_byte returns the next encrypted byte
/// @return    the next byte
static unsigned char next_byte() {
    index1 = (index1+1) % 256;
    index2 = (index2 + stream[index1]) % 256;
    unsigned char tmp = stream[index1];
    stream[index1] = stream[index2];
    stream[index2] = tmp;
    tmp = stream[(stream[index1] + stream[index2]) % 256];
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
    for(index1 = 0; index1 < 256; index1++) {
        stream[index1] = index1;
    }

    //randomize elements by swapping different indexes
    index2 = 0;
    for(index1 = 0; index1 < 256; index1++) {
        index2 = (index2 + stream[index1] + box->key[index1 % box->kelen]) % 256;
        unsigned char tmp = stream[index1];
        stream[index1] = stream[index2];
        stream[index2] = tmp;
    }
    //skip first 1024 bytes of KStream to prime system
    for(int i = 0; i < 1025; i++) {
        next_byte();
    }

    fclose(fp);
    return box;
}

kstreamADT ks_destroy(kstreamADT box) {
    free(box);
}

kstreamADT ks_translate(kstreamADT box) {

}
