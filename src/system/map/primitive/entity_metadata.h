#ifdef ENTITY_METADATA_H
#error "You're not supposed to include entity_metadata.h twice."
#endif

#define ENTITY_METADATA_H

#include "entity.h"

/*
 * - From entity.c
 * Set up the entities' metadatas here!
 */

const static struct{
/*
 * - From entity.c
 * Filepath of their png texture.
 */
    char filepath[64];
/*
 * - From entity.c
 * Image's scaling, scales width, height, and origin appropriately.
 */
    float scale;
/*
 * - From entity.c
 * Gameplay travel speed...
 */
    float speed;
/*
 * - From entity.c
 * Hitbox offset (not the origin).
 */
    struct{
        float x;    /* +1 = left    */
        float y;    /* +1 = up      */
    }hitbox_offset;
/*
 * - From entity.c
 * Hitbox size modification by adding the value set.
 */
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
    },
    { /* TO BE REMADE */
        "assets/textures/entity/rock.png",
        (float)1,
        (float)0,
        {
            (float)-13,
            (float)-12,
        },
        {
            (float)-19,
            (float)-20,
        }
    }
};