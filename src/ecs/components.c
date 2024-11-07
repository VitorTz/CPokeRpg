#include "components.h"
#include "../util/texture_pool.h"


void transform_init(transform_t* t, const zindex_t zindex) {
	t->pos.x = 0.0f;
	t->pos.y = 0.0f;
	t->size.x = 0.0f;
	t->size.y = 0.0f;
	t->zindex = zindex;
}

void sprite_init(sprite_t* sprite, const char* file_name) {
	sprite->texture = texture_pool_get(file_name);
}


void sprite_animation_init(
	sprite_animation_t* s,
	const char* file_name,
	const float width,
	const float height,
	uint8_t speed
) {
	s->texture = texture_pool_get(file_name);
	s->rect.x = 0.0f;
	s->rect.y = 0.0f;
	s->rect.width = width;
	s->rect.height = height;
	s->current_frame = 0;
	s->max_frame = speed;
	s->current_sprite_index = 0;
	s->max_sprite_index = (float) s->texture->width / width;
}