#pragma once
#include "components.h"
#include "../util/hash_map.h"


typedef struct component_manager {
	hash_map_t component_map[NUM_COMPONENTS];
} component_manager_t;


void component_manager_init(component_manager_t* c);

void component_manager_close(component_manager_t* c);

void component_manager_add(
	component_manager_t* c,
	entity_t e,
	component_t id,
	const void* data
);

void* component_manager_get(
	component_manager_t* c,
	entity_t e,
	component_t id
);


void component_manager_erase(
	component_manager_t* c,
	entity_t e,
	component_t id
);


void component_manager_entity_destroy(
	component_manager_t* c,
	entity_t e
);

void component_manager_clear(component_manager_t* c);