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

static struct texture tex_list[MAX_TILE_TYPE] = {0};

static char *_texfpath(int i){
    char fpath[TEX_STRLEN + sizeof(TEX_PATH)] = {0};
    return strcat(strcat(fpath, TEX_PATH), tex_pathlist[i]);
}

int tile_init(void){
    int i;
    for(i = 0; i < MAX_TILE_TYPE; i++){
        if(tex_load(&tex_list[i], _texfpath(i)))
            return -i;
    }
    return 0;
}

void tile_quit(void){
    int i;
    for(i = 0; i < MAX_TILE_TYPE; i++)
        tex_unload(&tex_list[i]);
}