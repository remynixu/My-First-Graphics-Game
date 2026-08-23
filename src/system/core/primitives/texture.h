#ifndef TEXTURE_H
#define TEXTURE_H

#include "types.h"

/* Texture that can be rendered. */
struct texture{
    unsigned int id;
    int width;
    int height;
    int mipmaps;
    int format;
};

/* Affects how a texture is rendered. */
struct texture_modifier{
    struct rectangle src;
    struct rectangle dst;
    struct vector2 org;
};

/* Loads the specified image (PNG). */
struct texture tex_load(const char *image_path);

void tex_draw(struct texture *tex, struct texture_modifier *mod);

#endif /* TEXTURE_H */