#include "image.h"


void pk::image_draw(const pk::image_t& image) {
	DrawTextureV(*image.texture, image.pos, WHITE);
}

void pk::image_draw_rect(const pk::image_t& img, const Rectangle& rect) {
	DrawTextureRec(*img.texture, rect, img.pos, WHITE);
}


void pk::image_set_center(pk::image_t& image, const Vector2 center) {
	image.pos.x = center.x - image.size.x / 2.0f;
	image.pos.y = center.y - image.size.y / 2.0f;
}