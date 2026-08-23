#include "tile.h"

#include "primitives/texture.h"

#include <string.h>

#define TEX_PATH    "assets/textures/tile/"
#define TEX_STRLEN  16

static const char tex_pathlist[MAX_TILE_TYPE][TEX_STRLEN] = {
    "null.png",
    "stone.png",
    "grass.png",
    "water.png"
};

static struct texture_info tex_infolist[MAX_TILE_TYPE] = {0};

static char *_texfpath(int i){
    char fpath[TEX_STRLEN + sizeof(TEX_PATH)] = {0};
    return strcat(strcat(fpath, TEX_PATH), tex_pathlist[i]);
}

int tile_init(void){
    int i;
    for(i = 0; i < MAX_TILE_TYPE; i++){
        if(texinfo_load(&tex_infolist[i], _texfpath(i)))
            return -i;
    }
    return 0;
}

struct texture_modifier _getmod(struct tile *t){
    struct texture_modifier mod = {0};
    return mod;
}

struct texture tile_gettex(struct tile *t){
    struct texture_info info = tex_infolist[t->type];
    struct texture_modifier mod = _getmod(t);
    struct texture tex;
    {
        tex.info = info;
        tex.mod = mod;
    }
    return tex;
}

void tile_quit(void){
    int i;
    for(i = 0; i < MAX_TILE_TYPE; i++)
        texinfo_unload(&tex_infolist[i]);
}