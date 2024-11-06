#pragma once
#include "assert.h"
#include "../util/vector.h"
#include "../util/types.h"
#include "../constants.h"


typedef struct entity_manager {
	vector_t vec;		
} entity_manager_t;


void entity_manager_init(entity_manager_t* ent);

void entity_manager_close(entity_manager_t* ent);

entity_t entity_manager_entity_create(entity_manager_t* ent);

void entity_manager_entity_destroy(entity_manager_t* ent, entity_t e);

void entity_manager_clear(entity_manager_t* ent);

size_t entity_manager_size(entity_manager_t* ent);
