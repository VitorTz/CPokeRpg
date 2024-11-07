#pragma once
#include "texture_pool.h"


typedef struct image {
	Texture2D* texture;
	Vector2 pos;
	Vector2 size;
} image_t;


void image_init(image_t* image, const char* file_name);

void image_draw(image_t* image);

void image_draw_rect(image_t* image, const Rectangle* rect);

void image_set_center(image_t* image, Vector2 center);
