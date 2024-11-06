#pragma once
#include "assert.h"
#include "../util/hash_map.h"
#include "../util/iterator.h"
#include "../util/vector.h"
#include "../util/types.h"
#include "../util/util.h"
#include "../constants.h"


typedef struct component_array {
	hash_map_t entity_to_index;
	hash_map_t index_to_entity;
	vector_t vec;	
} component_array_t;


void component_array_init(component_array_t* arr, size_t component_size);

void component_array_close(component_array_t* arr);

void* component_array_add(component_array_t* arr, entity_t e);

void* component_array_at(component_array_t* arr, entity_t e);

iterator_t component_array_iterator(component_array_t* arr);

void component_array_erase(component_array_t* arr, entity_t e);

void component_array_clear(component_array_t* arr);

size_t component_array_size(component_array_t* arr);
