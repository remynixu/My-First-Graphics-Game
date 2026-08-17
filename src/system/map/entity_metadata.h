#ifdef ENTITY_METADATA_H
#error "You're not supposed to include this twice."
#endif

#define ENTITY_METADATA_H

#include "entity.h"

const static struct{
    char filepath[64];
    float scale;
    float speed;
    struct{
        float x;    /* +1 = left    */
        float y;    /* +1 = up      */
    }hitbox_offset;
    struct{
        float width;    /* +1 = right   */
        float height;   /* +1 = down    */
    }hitbox_sizemod;
}_metadata_list[MAX_ENTITY_TYPE] = {
    {
        "assets/textures/entity/null.png",
        (float)1,
        (float)100,
        {0},
        {0}
    },
    {
        "assets/textures/entity/arundel.png",
        (float)1,
        (float)50,
        {
            (float)-9.5f,
            (float)-24
        },
        {
            (float)-18,
            (float)-27
        }
    }
};