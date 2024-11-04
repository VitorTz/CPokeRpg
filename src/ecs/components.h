#ifndef PK_COMPONENTS_H
#define PK_COMPONENTS_H
#include <raylib.h>
#include <stdint.h>
#include "../util/types.h"


#define NUM_COMPONENTS 3

extern size_t TRANSFORM_ID;
extern size_t SPRITE_ID;
extern size_t SPRITE_ANIMATION_ID;


typedef struct transform {
    Vector2 pos;
    Vector2 size;
    zindex_t zindex;    
} transform_t;


typedef struct sprite {
    Texture* texture;
} sprite_t;


typedef struct sprite_animation {
    Texture2D* texture;
    Rectangle rect;
    uint8_t current_frame;
    uint8_t max_frame;
    uint8_t current_sprite;
    uint8_t max_sprite;
} sprite_animation_t;


#endif