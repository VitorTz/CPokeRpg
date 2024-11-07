#include "entity_manager.h"
#include "../constants.h"


void entity_manager_init(entity_manager_t* e) {
	vector_init(&e->vec, sizeof(entity_t));
	vector_reserve(&e->vec, MAX_ENTITIES);
	for (entity_t ent = 0; ent < MAX_ENTITIES; ent++) {
		const entity_t i = MAX_ENTITIES - ent - 1;
		vector_push_back(&e->vec, &i);
	}
	e->size = 0;	
}


void entity_manager_close(entity_manager_t* e) {
	vector_close(&e->vec);
}


entity_t entity_manager_entity_create(entity_manager_t* e) {
	entity_t ent;
	vector_pop_back(&e->vec, &ent);
	e->size++;
	return ent;
}


void entity_manager_entity_destroy(entity_manager_t* e, const entity_t ent) {
	vector_push_back(&e->vec, &ent);
	e->size--;
}


void entity_manager_clear(entity_manager_t* e) {
	vector_clear(&e->vec);
	for (entity_t ent = 0; ent < MAX_ENTITIES; ent++) {
		const entity_t i = MAX_ENTITIES - ent - 1;
		vector_push_back(&e->vec, &i);
	}
	e->size = 0;
}


size_t entity_manager_size(entity_manager_t* e) {
	return e->size;
}