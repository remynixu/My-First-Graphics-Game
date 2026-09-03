#ifndef MD_PIXEL_H

/*
 * This header's only job is to define and handle a pixel.
 */
#define MD_PIXEL_H

#include "../lib/l_type.h"

/*
 * We do not rely on structs or stuff like that. For us—or rather, this current
 * implementation—a pixel is an array of four bytes: Red, Green, Blue, Alpha.
 */
#define MD_PIXEL_BYTE_SIZE  4

/*
 * It's a config because we don't actually know if the pixel of this platform is
 * the usual RGBA or whatever—is it big endian? Little endian? It's still too
 * platform dependent for this game's portability standards.
 */
struct pixel_config{
    byte r;
    byte g;
    byte b;
    byte a;
};

/*
 * Initializes a pixel.
 */
void md_pixel_set(byte pixel[static MD_PIXEL_BYTE_SIZE], const struct pixel_config hint);

/*
 * Gets the data of a pixel.
 */
void md_pixel_get(const byte pixel[static MD_PIXEL_BYTE_SIZE], struct pixel_config *const config);

/*
 * Copies a pixel's values to another pixel.
 */
void md_pixel_copy(byte pixel_dest[static MD_PIXEL_BYTE_SIZE], const byte pixel_src[static MD_PIXEL_BYTE_SIZE]);

#endif /* MD_PIXEL_H */