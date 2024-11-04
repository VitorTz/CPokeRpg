#include <assert.h>
#include <stdlib.h>
#include "component_manager.h"
#include "component_array.h"
#include "components.h"


component_manager_t* component_manager_create() {
    component_manager_t* c = malloc(sizeof(component_manager_t));
    component_array_init(&c->components[TRANSFORM_ID], sizeof(transform_t));
    component_array_init(&c->components[SPRITE_ID], sizeof(sprite_t));
    component_array_init(&c->components[SPRITE_ANIMATION_ID], sizeof(SPRITE_ANIMATION_ID));
    return c;
}


void component_manager_register_component(
    component_manager_t* const c_manager, 
    const size_t component_size, 
    const size_t component_id
) {    
    component_array_init(&c_manager->components[component_id], component_size);
}


void component_manager_destroy(component_manager_t* const c_manager) {
    for (int i = 0; i < NUM_COMPONENTS; i++) {
        component_array_t* arr = &c_manager->components[i];
        hash_map_destroy(arr->entity_to_index);
        hash_map_destroy(arr->index_to_entity);
        free(arr->data);
    }
    free(c_manager);
}


void* component_manager_get(
    component_manager_t* const c_manager, 
    const entity_t e, 
    const component_t component_id
) {    
    return component_array_at(&c_manager->components[component_id], e);
}


void component_manager_erase(
    component_manager_t* const c_manager, 
    const entity_t e, 
    const component_t component_id
) {    
    component_array_erase(&c_manager->components[component_id], e);
}


void component_manager_clear(component_manager_t* const c_manager) {
    for (int i = 0; i < NUM_COMPONENTS; i++) {
        component_array_clear(&c_manager->components[i]);
    }    
}