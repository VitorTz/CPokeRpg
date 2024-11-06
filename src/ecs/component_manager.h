#pragma once
#include "assert.h"
#include "components.h"
#include "component_array.h"


typedef struct component_manager {
	component_array_t component_array_vec[NUM_COMPONENTS];
} component_manager_t;


void component_manager_init(component_manager_t* c_manager);

void component_manager_close(component_manager_t* c_manager);

void* component_manager_add(component_manager_t* c_manager, entity_t e, size_t component_id);

void* component_manager_at(component_manager_t* c_manager, entity_t e, size_t component_id);

void component_manager_erase(component_manager_t* c_manager, entity_t e, size_t component_id);

void component_manager_clear(component_manager_t* c_manager, size_t component_id);

iterator_t component_manager_iterator(component_manager_t* c_manager, size_t component_id);


