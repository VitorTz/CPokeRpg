#pragma once
#include "assert.h"
#include "components.h"
#include "../util/util.h"
#include "../util/hash_map.h"
#include "../util/hash_set.h"
#include "../constants.h"


typedef struct system {
	void (*update)(const float, hash_set_t* set);
	void (*draw)(entity_t e);
} system_t;


typedef struct system_manager {
	hash_map_t system_map;
	hash_map_t component_to_entities;
	hash_map_t entity_to_drawable_components;
	hash_set_t drawable_components;
	vector_t update_order;
} system_manager_t;


void system_manager_init(system_manager_t* s);

void system_manager_close(system_manager_t* s);

void system_manager_add(
	system_manager_t* s,
	entity_t e,
	component_t id
);

void system_manager_erase(
	system_manager_t* s,
	entity_t e,
	component_t id
);

void system_manager_update(system_manager_t* s, float dt);

void system_manager_draw(system_manager_t* s, vector_t* entities);

void system_manager_entity_destroy(system_manager_t* s, entity_t e);

void system_manager_clear(system_manager_t* s);


// Systems
void sprite_draw(entity_t e);

void sprite_animation_update(const float dt, hash_set_t* set);

void sprite_animation_draw(entity_t e);