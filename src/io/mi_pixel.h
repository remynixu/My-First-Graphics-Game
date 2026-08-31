#ifndef MI_PIXEL_H
#define MI_PIXEL_H

#include "../lib/l_type.h"

/*
 * We do not rely on structs or stuff like that. For us, a pixel is an array
 * of four bytes: Red, Green, Blue, Alpha.
 */

#define MI_PIXEL_BYTE_SIZE  4

/*
 * Copies a pixel's values to another pixel.
 */

void mi_pixel_copy(byte pixel_dest[static MI_PIXEL_BYTE_SIZE], const byte pixel_src[static MI_PIXEL_BYTE_SIZE]);

#endif /* MI_PIXEL_H */