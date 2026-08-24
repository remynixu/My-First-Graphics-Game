#ifndef TEXTURE_H
#define TEXTURE_H

#include "types.h"

/* A texture's information for rendering. */
struct texture_info{
    unsigned int id;
    int width;
    int height;
    int mipmaps;
    int format;
};

/* Affects how a texture is rendered. */
struct draw_modifier{
    struct rectangle src;
    struct rectangle dst;
    struct vector2 org;
};

/* Full texture info. */
struct texture{
    struct texture_info info;
    struct draw_modifier mod;
};

/* Loads the specified image (PNG). */
int texinfo_load(struct texture_info *info, const char *image_path);

/* Draws a texture to screen (Needs a window, see window.h for more info). */
void tex_draw(struct texture *tex);

/* Unloads a texture from memory. */
void texinfo_unload(struct texture_info *info);

#ifdef _TEXTURE_CONVERTIONS

#define t2d_to_texinfo(t2d, texinfo)    \
do{                                     \
    (texinfo).id = (t2d).id;            \
    (texinfo).width = (t2d).width;      \
    (texinfo).height = (t2d).height;    \
    (texinfo).mipmaps = (t2d).mipmaps;  \
    (texinfo).format = (t2d).format;    \
}while(0)

/*
 * impltex is the implementation-specific texture while texinfo is texture.h's
 * texture info definition.
 */
#define impltex_to_texinfo(impltex, texinfo)  t2d_to_texinfo(impltex, texinfo)

#endif /* _TEXTURE_CONVERTIONS */

#endif /* TEXTURE_H */
