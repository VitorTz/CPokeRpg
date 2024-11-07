#include <assert.h>
#include "component_manager.h"
#include "../util/util.h"


void component_manager_init(component_manager_t* c) {
	hash_map_init(&c->component_map[TRANSFORM_ID], sizeof(transform_t), NUM_COMPONENTS / 4, hash_entity_t);	
	hash_map_init(&c->component_map[SPRITE_ID], sizeof(sprite_t), NUM_COMPONENTS / 4, hash_entity_t);	
	hash_map_init(&c->component_map[SPRITE_ANIMATION_ID], sizeof(sprite_animation_t), NUM_COMPONENTS / 4, hash_entity_t);	
}


void component_manager_close(component_manager_t* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_map_close(c->component_map + i);
	}
}


void component_manager_add(
	component_manager_t* c,
	const entity_t e,
	const component_t id,
	const void* data
) {
	hash_map_insert(c->component_map + id, &e, data);	
}


void* component_manager_get(
	component_manager_t* c,
	const entity_t e,
	const component_t id
) {
	return hash_map_at(c->component_map + id, &e);
}


void component_manager_erase(
	component_manager_t* c,
	const entity_t e,
	const component_t id
) {
	hash_map_erase(c->component_map + id, &e);
}


void component_manager_entity_destroy(
	component_manager_t* c,
	const entity_t e
) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_map_erase(c->component_map + i, &e);
	}
}


void component_manager_clear(component_manager_t* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_map_clear(c->component_map + i);
	}
}