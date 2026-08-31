#ifndef L_TYPE_H
#define L_TYPE_H

typedef unsigned char byte;

/* Not a complete guarantee, just looks fancy :> */
#define RODATA  static const

/*
 * If the data is uninitialized, it has a high chance of ending up on .bss;
 * if the data is initialized, it will probably end up on .data section.
 */

#define DATA    static

#endif /* L_TYPE_H */