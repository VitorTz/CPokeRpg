#include <assert.h>
#include "component_manager.h"
#include "component_array.h"
#include "components.h"


void component_manager_init(component_manager_t* c) {
    component_array_init(&c->components[TRANSFORM_ID], sizeof(transform_t));
    component_array_init(&c->components[SPRITE_ID], sizeof(sprite_t));
    component_array_init(&c->components[SPRITE_ANIMATION_ID], sizeof(sprite_animation_t));
}


void component_manager_close(component_manager_t* const c) {
    for (int i = 0; i < NUM_COMPONENTS; i++) {        
        component_array_close(&c->components[i]);
    }
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