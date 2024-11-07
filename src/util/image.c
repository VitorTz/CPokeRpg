#include "image.h"


void image_init(image_t* image, const char* file_name) {
	image->texture = texture_pool_get(file_name);
	image->size.x = (float)image->texture->width;
	image->size.y = (float)image->texture->height;
	image->pos.x = 0.0f;
	image->pos.y = 0.0;
}


void image_draw(image_t* image) {
	DrawTextureV(*image->texture, image->pos, WHITE);
}


void image_draw_rect(image_t* image, const Rectangle* rect) {
	DrawTextureRec(*image->texture, *rect, image->pos, WHITE);
}

void image_set_center(image_t* image, const Vector2 center) {
	image->pos.x = center.x - image->size.x / 2.0f;
	image->pos.y = center.y - image->size.y / 2.0f;
}