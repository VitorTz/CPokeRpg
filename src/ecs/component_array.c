#include "../constants.h"
#include <assert.h>
#include "component_array.h"
#include <stdlib.h>
#include <string.h>


component_array_t* component_array_create(const size_t component_size) {
    component_array_t* arr = malloc(sizeof(component_array_t));
    component_array_init(arr, component_size);
    return arr;
}


void component_array_init(component_array_t *arr, const size_t component_size) {
    arr->entity_to_index = hash_map_create(MAX_ENTITIES / 2, sizeof(size_t));
    arr->index_to_entity = hash_map_create(MAX_ENTITIES / 2, sizeof(entity_t));
    arr->data = malloc(component_size * MAX_ENTITIES);
    arr->c_size = component_size;
    arr->size = 0;
}


void component_array_destroy(component_array_t* const arr) {
    hash_map_destroy(arr->entity_to_index);
    hash_map_destroy(arr->index_to_entity);
    free(arr->data);
    free(arr);
}


void* component_array_at(component_array_t* arr, const entity_t e) {
    hash_map_query_t q = hash_map_contains(arr->entity_to_index, e);
    assert(q.success);
    const size_t* i = (size_t*) q.data;
    return arr->data + *i * arr->c_size;
}


void component_array_erase(component_array_t *arr, const entity_t e) {
    hash_map_query_t q = hash_map_contains(arr->entity_to_index, e);
    if (!q.success) {
        return;
    }
    
    const size_t last_index = arr->size - 1;
    const size_t removed_component_index = *((size_t*) q.data);
    const entity_t last_entity = *((size_t*) hash_map_at(arr->index_to_entity, last_index));
    
    void* src = arr->data + last_index * arr->c_size;
    void* dst = arr->data + removed_component_index * arr->c_size;
    memcpy(dst, src, arr->c_size);

    *((size_t*) hash_map_at(arr->entity_to_index, last_entity)) = removed_component_index;    

    *((entity_t*) hash_map_at(arr->index_to_entity, removed_component_index)) = last_entity;    

    hash_map_erase(arr->entity_to_index, e);
    hash_map_erase(arr->index_to_entity, last_index);

    arr->size--;
}


void component_array_clear(component_array_t *arr) {
    hash_map_clear(arr->entity_to_index);
    hash_map_clear(arr->index_to_entity);
    arr->size = 0;
}