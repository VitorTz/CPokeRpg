#include "vector_entity.h"


void vector_entity_init(vector_entity_t* vec) {
	vector_init(&vec->vec, sizeof(entity_pair_t));
	vector_reserve(&vec->vec, MAX_ENTITIES);
}


void vector_entity_close(vector_entity_t* vec) {
	vector_close(&vec->vec);
}


void vector_entity_push_back(vector_entity_t* vec, entity_pair_t* pair) {
	*((entity_pair_t*)vector_allocate(vec)) = *pair;
}


void vector_entity_clear(vector_entity_t* vec) {
	vector_clear(&vec->vec);
}


iterator_t vector_entity_iterator(vector_entity_t* vec) {
	return vector_iterator(&vec->vec);
}