#pragma once
#include "../util/vector.h"
#include "../util/types.h"


typedef struct entity_manager {
	vector_t vec;	
	size_t size;
} entity_manager_t;


void entity_manager_init(entity_manager_t*  e);

void entity_manager_close(entity_manager_t* e);

entity_t entity_manager_entity_create(entity_manager_t* e);

void entity_manager_entity_destroy(entity_manager_t* e, entity_t ent);

void entity_manager_clear(entity_manager_t* e);

size_t entity_manager_size(entity_manager_t* e);