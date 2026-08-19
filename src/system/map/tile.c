#include "tile.h"

Rectangle get_tile_hitbox(const struct tile *const t){
    Rectangle hb;
    hb.height = (float)TILE_PIXEL_HEIGHT;
    hb.width = (float)TILE_PIXEL_WIDTH;
    hb.x = (float)t->x;
    hb.y = (float)t->y;
    return hb;
}

static const char tex_pathlist[MAX_TILE_TYPE][64] = {
    "assets/textures/tile/null.png",
    "assets/textures/tile/stone.png",
    "assets/textures/tile/grass.png",
    "assets/textures/tile/water.png"
};

static Texture2D tex_list[MAX_TILE_TYPE] = {0};

static int _load_tex(const int i){
    tex_list[i] = LoadTexture(tex_pathlist[i]);
    if(!IsTextureValid(tex_list[i])){
        UnloadTexture(tex_list[i]);
        return -1;
    }
    SetTextureFilter(tex_list[i], TEXTURE_FILTER_POINT);
    return 0;
}

int load_tile_textures(void){
    int i;
    int errcode;
    for(i = 0; i < MAX_TILE_TYPE; i++){
        errcode =_load_tex(i);
        if(errcode == -1)
            return -(i + 1);
    }
    return 0;
}

static int _rand(const int seed){
    return (unsigned int)((seed * 1103515245 + 12345)/65536) % 32768;
}

enum tile_mode{
    TILE_IDLE = 0,
    TILE_VARIED,
    TILE_ANIMATED
};

float tile_animation_time = 0.0f;

/*
 * Expected spritesheet:
 *
 * ANIMATION | VARIANTS --------->
 * |
 * |
 * V
 */

Rectangle prepare_tile(const struct tile *const t, const int seed){
    enum tile_mode mode;
    Rectangle hint = {0};
    {
        hint.width = TILE_PIXEL_WIDTH;
        hint.height = TILE_PIXEL_HEIGHT;
        hint.x = hint.y = 0;
    }
    switch(t->type){
        case TILE_GRASS:
            mode = TILE_VARIED;
        break;
        case TILE_WATER:
            mode = TILE_ANIMATED;
        break;
        case TILE_NULL:
        case TILE_STONE:
        default:
            mode = TILE_IDLE;
        break;
    }
    switch(mode){
        case TILE_VARIED:{
            int _vary_amount = tex_list[t->type].width / TILE_PIXEL_WIDTH;
            int _variant_index = _rand(seed) % _vary_amount;
            hint.x += TILE_PIXEL_WIDTH * _variant_index;
        }
        break;
        case TILE_ANIMATED:{
            int _frame_index = 0;
            if(tile_animation_time > 0.25) _frame_index++;
            if(tile_animation_time > 0.50) _frame_index++;
            if(tile_animation_time > 0.75) _frame_index++;
            hint.y += TILE_PIXEL_HEIGHT * _frame_index;
        }
        break;
        case TILE_IDLE:
        default:
        break;
    }
    return hint;
}

void draw_tile(const struct tile *const t, Rectangle src_hint){
    Vector2 origin = {0};
    Rectangle dst;
    dst.height = (float)TILE_PIXEL_HEIGHT;
    dst.width = (float)TILE_PIXEL_WIDTH;
    dst.x = (float)t->x;
    dst.y = (float)t->y;
    DrawTexturePro(tex_list[t->type], src_hint, dst, origin, 0.0f, WHITE);
}

static void _free_tile(const int i){
    UnloadTexture(tex_list[i]);
}

void free_tile_textures(void){
    int i = 0;
    for(i = 0; i < MAX_TILE_TYPE; i++)
        _free_tile(i);
}