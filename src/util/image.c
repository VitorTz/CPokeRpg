#include "image.h"


void image_init(image_t* img, const char* file_name) {
	img->texture = texture_pool_get(file_name);
	img->size.x = (float) img->texture->width;
	img->size.y = (float)img->texture->height;
	img->pos.x = 0.0f;
	img->pos.y = 0.0f;
}


void image_draw(image_t* img) {
	DrawTextureV(*img->texture, img->pos, WHITE);
}


void image_draw_rect(image_t* img, Rectangle* rect) {
	DrawTextureRec(*img->texture, *rect, img->pos, WHITE);
}


void image_set_center(image_t* img, const Vector2 center) {
	img->pos.x = center.x - img->size.x / 2.0f;
	img->pos.y = center.y - img->size.y / 2.0f;
}


void image_set_topleft(image_t* img, const Vector2 topleft) {
	img->pos.x = topleft.x;
	img->pos.y = topleft.y;
}