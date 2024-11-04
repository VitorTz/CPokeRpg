#ifndef PK_COMPONENT_ARRAY_H
#define PK_COMPONENT_ARRAY_H
#include <stdlib.h>
#include "../util/types.h"
#include "../util/hash_map.h"


typedef struct component_array {
    hash_map_t entity_to_index;
    hash_map_t index_to_entity;
    size_t c_size;
    size_t size;
    char* data;
} component_array_t;


void component_array_init(component_array_t* arr, size_t component_size);

void component_array_close(component_array_t* arr);

void* component_array_at(component_array_t* arr, entity_t e);

void component_array_erase(component_array_t* arr, entity_t e);

void component_array_clear(component_array_t* arr);


#endif