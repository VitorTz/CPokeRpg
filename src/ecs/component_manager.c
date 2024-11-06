#include "component_manager.h"


void component_manager_init(component_manager_t* c_manager) {
	component_array_init(c_manager->component_array_vec + TRANSFORM_ID, sizeof(transform_t));
	component_array_init(c_manager->component_array_vec + SPRITE_ID, sizeof(sprite_t));
	component_array_init(c_manager->component_array_vec + SPRITE_ANIMATION_ID, sizeof(sprite_animation_t));
}


void component_manager_close(component_manager_t* c_manager) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		component_array_close(c_manager->component_array_vec + i);
	}
}


void* component_manager_add(component_manager_t* c_manager, const entity_t e, const size_t component_id) {	
	return component_array_add(c_manager->component_array_vec + component_id, e);
}


void* component_manager_at(component_manager_t* c_manager, const entity_t e, const size_t component_id) {	
	return component_array_at(c_manager->component_array_vec + component_id, e);
}


void component_manager_erase(component_manager_t* c_manager, const entity_t e, const size_t component_id) {	
	component_array_erase(c_manager->component_array_vec + component_id, e);
}


void component_manager_clear(component_manager_t* c_manager, const size_t component_id) {	
	component_array_clear(c_manager->component_array_vec + component_id);
}


iterator_t component_manager_iterator(component_manager_t* c_manager, const size_t component_id) {
	return component_array_iterator(c_manager->component_array_vec + component_id);
}