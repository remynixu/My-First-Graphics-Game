#include "md_pixel.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The code below is expected to be different for different platforms.
 */

#define PIXEL_R_INDEX   0
#define PIXEL_G_INDEX   1
#define PIXEL_B_INDEX   2
#define PIXEL_A_INDEX   3

void md_pixel_set(byte pxl[static MD_PIXEL_BYTE_SIZE], const struct pixel_config h){
    pxl[PIXEL_R_INDEX] = h.r;
    pxl[PIXEL_G_INDEX] = h.g;
    pxl[PIXEL_B_INDEX] = h.b;
    pxl[PIXEL_A_INDEX] = h.a;
}

void md_pixel_get(const byte pxl[static MD_PIXEL_BYTE_SIZE], struct pixel_config *const conf){
    conf->r = pxl[PIXEL_R_INDEX];
    conf->g = pxl[PIXEL_G_INDEX];
    conf->b = pxl[PIXEL_B_INDEX];
    conf->a = pxl[PIXEL_A_INDEX];
}

void md_pixel_copy(byte _dst[static MD_PIXEL_BYTE_SIZE], const byte _src[static MD_PIXEL_BYTE_SIZE]){
    int i;
    for(i = 0; i < MD_PIXEL_BYTE_SIZE; i++)
        _dst[i] = _src[i];
}