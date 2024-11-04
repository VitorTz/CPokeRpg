#ifndef PK_HASH_MAP_H
#define PK_HASH_MAP_H
#include <stdlib.h>
#include <stddef.h>
#include "vector.h"


typedef struct hash_map {
    vector_t* buckets;
    size_t num_buckets;
    size_t t_size;
    size_t size;
} hash_map_t;


typedef struct hash_map_query {
    int success;
    char* data;
} hash_map_query_t;


typedef struct hash_map_iterator {
    vector_t* begin;
    vector_t* end;
    size_t step;
} hash_map_iterator_t;


void hash_map_init(hash_map_t* hash_map, size_t num_buckets, size_t t_size);

void hash_map_close(hash_map_t* hash_map);

void* hash_map_at(hash_map_t* hash_map, size_t key);

int hash_map_erase(hash_map_t* hash_map, size_t key);

void hash_map_clear(hash_map_t* hash_map);

hash_map_iterator_t hash_map_get_iterator(hash_map_t* hash_map);

hash_map_query_t hash_map_contains(hash_map_t* hash_map, size_t key);


#endif