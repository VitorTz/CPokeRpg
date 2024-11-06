#include "entity_manager.h"


void entity_manager_init(entity_manager_t* ent) {
	vector_init(&ent->vec, sizeof(entity_t));
	vector_reserve(&ent->vec, MAX_ENTITIES);
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		*((entity_t*) vector_allocate(&ent->vec)) = e;
	}
}


void entity_manager_close(entity_manager_t* ent) {
	vector_close(&ent->vec);	
}


entity_t entity_manager_entity_create(entity_manager_t* ent) {
	assert(ent->vec.size != 0);
	const entity_t e = vector_at(&ent->vec, --ent->vec.size);
	vector_erase(&ent->vec, ent->vec.size);
	return e;
}


void entity_manager_entity_destroy(entity_manager_t* ent, const entity_t e) {
	*((entity_t*)vector_allocate(&ent->vec)) = e;
}


void entity_manager_clear(entity_manager_t* ent) {
	vector_clear(&ent->vec);
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		*((entity_t*)vector_allocate(&ent->vec)) = e;
	}
}


size_t entity_manager_size(entity_manager_t* ent) {
	return ent->vec.size;
}