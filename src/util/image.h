#pragma once
#include <raylib.h>
#include "texture_pool.h"


typedef struct image {
	Texture2D* texture;
	Vector2 pos;
	Vector2 size;
} image_t;


void image_init(image_t* img, const char* file_name);


void image_draw(image_t* img);


void image_draw_rect(image_t* img, Rectangle* rect);


void image_set_center(image_t* img, Vector2 center);


void image_set_topleft(image_t* img, Vector2 topleft);
