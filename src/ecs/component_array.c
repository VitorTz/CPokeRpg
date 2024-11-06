#include "component_array.h"


void component_array_init(component_array_t* arr, const size_t component_size) {
	hash_map_init(
		&arr->entity_to_index, 
		sizeof(size_t), 
		MAX_ENTITIES / 4, 
		hash_entity_t
	);
	hash_map_init(
		&arr->index_to_entity,
		sizeof(entity_t),
		MAX_ENTITIES / 4,
		hash_size_t
	);
	vector_init(&arr->vec, component_size);
}


void component_array_close(component_array_t* arr) {
	hash_map_close(&arr->entity_to_index);
	hash_map_close(&arr->index_to_entity);
	vector_close(&arr->vec);
}


void* component_array_add(component_array_t* arr, const entity_t e) {
	const hash_map_query_t q = hash_map_try_insert(&arr->entity_to_index, &e);
	// Se conseguiu inserir, então não existe um par com chave == e no mapa;
	assert(q.success);
	*((size_t*) q.data) = arr->vec.size;
	*((entity_t*)hash_map_insert(&arr->index_to_entity, &arr->vec.size)) = e;
	return vector_allocate(&arr->vec);
}


void* component_array_at(component_array_t* arr, const entity_t e) {
	const hash_map_query_t q = hash_map_contains(&arr->entity_to_index, &e);
	assert(q.success);
	return vector_at(&arr->vec, *((size_t*) q.data));
}


iterator_t component_array_iterator(component_array_t* arr) {
	const iterator_t iter = vector_iterator(&arr->vec);
	return iter;
}


void component_array_erase(component_array_t* arr, const entity_t e) {
	const hash_map_query_t q = hash_map_contains(&arr->entity_to_index, &e);
	if (!q.success) {
		return;
	}
	const size_t last_index = arr->vec.size - 1;
	const size_t removed_component_index = *((size_t*)q.data);
	const entity_t last_entity = *((entity_t*)hash_map_at(&arr->index_to_entity, &last_index));

	vector_erase(&arr->vec, removed_component_index);

	*((size_t*)hash_map_at(&arr->entity_to_index, &last_entity)) = removed_component_index;
	*((size_t*)hash_map_at(&arr->index_to_entity, &removed_component_index)) = last_entity;

	hash_map_erase(&arr->entity_to_index, &e);
	hash_map_erase(&arr->index_to_entity, &last_index);
}


void component_array_clear(component_array_t* arr) {
	hash_map_clear(&arr->entity_to_index);
	hash_map_clear(&arr->index_to_entity);
	vector_clear(&arr->vec);
}

size_t component_array_size(component_array_t* arr) {
	return arr->vec.size;
}