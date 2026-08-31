#include "mi_pixel.h"

void mi_pixel_copy(byte _dst[static MI_PIXEL_BYTE_SIZE], const byte _src[static MI_PIXEL_BYTE_SIZE]){
    _dst[0] = _src[0];
    _dst[1] = _src[1];
    _dst[2] = _src[2];
    _dst[3] = _src[3];
}