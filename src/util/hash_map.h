#ifndef PK_HASH_MAP_H
#define PK_HASH_MAP_H
#include <stdlib.h>
#include <stddef.h>
#include "iterator.h"
#include "vector.h"


typedef struct hash_node {
    size_t key;
    char* value;
} hash_node_t;


typedef struct hash_map {
    vector_t** buckets;
    size_t num_buckets;
    size_t t_size;
    size_t size;
} hash_map_t;


typedef struct hash_map_query {
    int success;
    void* data;
} hash_map_query_t;

typedef struct hash_map_iterator {
    iterator_t* iterators;
    size_t num_iterators;    
} hash_map_iterator_t;


hash_map_t* hash_map_create(size_t num_buckets, size_t t_size);

void hash_map_destroy(hash_map_t* hash_map);

void* hash_map_at(hash_map_t* hash_map, size_t key);

void hash_map_erase(hash_map_t* hash_map, size_t key);

void hash_map_clear(hash_map_t* hash_map);

hash_map_iterator_t hash_map_get_iterator(hash_map_t* hash_map);

void hash_map_iterator_destroy(hash_map_iterator_t* iterator);

hash_map_query_t hash_map_contains(hash_map_t* hash_map, size_t key);


#endif