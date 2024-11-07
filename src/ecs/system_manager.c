#include "system_manager.h"


static component_t transform_id = TRANSFORM_ID;
static component_t sprite_id = SPRITE_ID;
static component_t sprite_animation_id = SPRITE_ANIMATION_ID;


static system_t sprite_system = { NULL, sprite_draw };
static system_t sprite_animation_system = { sprite_animation_update, sprite_animation_draw };


void system_manager_init(system_manager_t* s) {
	// Register systems
	hash_map_init(&s->system_map, sizeof(system_t), NUM_COMPONENTS, hash_component_t);
	hash_map_insert(&s->system_map, &sprite_id, &sprite_system);
	hash_map_insert(&s->system_map, &sprite_animation_id, &sprite_animation_system);

	// Register one set of entities for each component
	hash_map_init(&s->component_to_entities, sizeof(hash_set_t), NUM_COMPONENTS, hash_component_t);	
	for (component_t id = 0; id < NUM_COMPONENTS; id++) {
		hash_map_query_t q = hash_map_allocate(&s->component_to_entities, &id);
		hash_set_t* hash_set = (hash_set_t*)q.value;
		hash_set_init(hash_set, sizeof(entity_t), MAX_ENTITIES / 4, hash_entity_t, equal_entity_t);
	}

	// Register one set of drawable components for each entity
	hash_map_init(&s->entity_to_drawable_components, sizeof(vector_t), MAX_ENTITIES / 4, hash_entity_t);	
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		hash_map_query_t q = hash_map_allocate(&s->entity_to_drawable_components, &e);
		vector_init((vector_t*) q.value, sizeof(component_t));
	}

	// Register drawable components
	hash_set_init(&s->drawable_components, sizeof(component_t), NUM_COMPONENTS, hash_component_t, equal_component_t);
	hash_set_insert(&s->drawable_components, &sprite_id);
	hash_set_insert(&s->drawable_components, &sprite_animation_id);

	// Update system order
	vector_init(&s->update_order, sizeof(component_t));
	vector_push_back(&s->update_order, &sprite_animation_id);
}


void system_manager_close(system_manager_t* s) {
	hash_map_close(&s->system_map);
	hash_map_close(&s->component_to_entities);
	hash_map_close(&s->entity_to_drawable_components);
	hash_set_close(&s->drawable_components);
	vector_close(&s->update_order);
}


void system_manager_add(system_manager_t* s, const entity_t e, const component_t id) {
	hash_set_t* set = (hash_set_t*) hash_map_at(&s->component_to_entities, &id);	
	hash_set_insert(set, &e);
	if (hash_set_contains(&s->drawable_components, &id)) {
		vector_t* vec = (vector_t*) hash_map_at(&s->entity_to_drawable_components, &e);
		vector_push_back(vec, &id);		
	}
}


void system_manager_erase(system_manager_t* s, const entity_t e, const component_t id) {
	hash_set_t* set = (hash_set_t*) hash_map_at(&s->component_to_entities, &id);
	hash_set_erase(set, &id);	
	vector_t* vec = hash_map_at(&s->entity_to_drawable_components, &e);	
	size_t i = 0;
	for (size_t i = 0; i < vec->size; i++) {
		if (*((component_t*)vector_at(vec, i)) == id) {
			vector_erase(vec, i);
		}
	}	
}


void system_manager_update(system_manager_t* s, const float dt) {
	const iterator_t iter_ids = vector_iterator(&s->update_order);
	for (component_t* id = iter_ids.begin; id < iter_ids.end; id++) {
		system_t* system = (system_t*) hash_map_at(&s->system_map, id);
		hash_set_t* entities_set = (hash_set_t*) hash_map_at(&s->component_to_entities, id);
		system->update(dt, entities_set);
	}
}


void system_manager_draw(system_manager_t* s, vector_t* entities) {
	const iterator_t iter = vector_iterator(entities);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		entity_t* e = (entity_t*) p;
		vector_t* vec = hash_map_at(&s->entity_to_drawable_components, e);
		const iterator_t viter = vector_iterator(vec);
		for (component_t* id = viter.begin; id < viter.end; id++) {
			system_t* system = hash_map_at(&s->system_map, id);
			system->draw(*e);
		}
	}
}


void system_manager_entity_destroy(system_manager_t* s, const entity_t e) {
	const vec_iterator_t iter = hash_map_get_vec_iterator(&s->component_to_entities);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		const iterator_t viter = vector_iterator(v);
		for (char* p = viter.begin; p < viter.end; p += viter.step) {
			hash_set_t* set = (hash_set_t*)(p + sizeof(size_t));
			hash_set_erase(set, &e);
		}
	}
	vector_t* vec = hash_map_at(&s->entity_to_drawable_components, &e);
	vector_clear(vec);
}


void system_manager_clear(system_manager_t* s) {
	hash_map_clear(&s->system_map);
	hash_map_clear(&s->component_to_entities);
	hash_map_clear(&s->entity_to_drawable_components);
	hash_set_clear(&s->drawable_components);	
}


void sprite_draw(const entity_t e) {
	
}


void sprite_animation_update(const float dt, hash_set_t* set) {

}


void sprite_animation_draw(const entity_t e) {

}