#ifndef TEXTURE_H
#define TEXTURE_H

#include "types.h"

/* Texture that can be rendered. */
struct texture_info{
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

/* Full texture info. */
struct texture{
    struct texture_info info;
    struct texture_modifier mod;
};

/* Loads the specified image (PNG). */
int texinfo_load(struct texture_info *info, const char *image_path);

void tex_draw(struct texture *tex);

/* Unloads a texture from memory. */
void texinfo_unload(struct texture_info *info);

#endif /* TEXTURE_H */