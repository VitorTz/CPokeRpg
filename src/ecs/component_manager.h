#ifndef PK_COMPONENT_MANAGER_H
#define PK_COMPONENT_MANAGER_H
#include "../util/types.h"
#include "component_array.h"
#include "components.h"


typedef struct component_manager {
    component_array_t components[NUM_COMPONENTS];
} component_manager_t;


component_manager_t* component_manager_create();

void component_manager_destroy(component_manager_t* c_manager);

void component_manager_register_component(component_manager_t* c_manager, size_t component_size, size_t component_id);

void* component_manager_get(component_manager_t* c_manager, entity_t e, component_t component_id);

void component_manager_erase(component_manager_t* c_manager, entity_t e, component_t id);

void component_manager_clear(component_manager_t* c_manager);


#endif