#include "components.h"


void sprite_init(sprite_t* sprite, const char* file_name) {
	sprite->texture = texture_pool_get(file_name);
}


void sprite_animation_init(
	sprite_animation_t* sprite_animation,
	const char* file_name,
	const float width,
	const float height,
	const uint8_t speed
) {
	sprite_animation->texture = texture_pool_get(file_name);
	sprite_animation->rect.x = 0.0f;
	sprite_animation->rect.y = 0.0f;
	sprite_animation->rect.width = width;
	sprite_animation->rect.height = height;
	sprite_animation->current_frame = 0;
	sprite_animation->max_frame = speed;
	sprite_animation->current_sprite_index = 0;
	sprite_animation->max_sprite_index = (float) sprite_animation->texture->width / width;	
}


void transform_init(transform_t* transform, const zindex_t zindex) {
	transform->pos.x = 0.0f;
	transform->pos.y = 0.0f;
	transform->size.x = 0.0f;
	transform->size.y = 0.0f;
	transform->zindex = zindex;
}