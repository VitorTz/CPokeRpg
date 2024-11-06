#pragma once
#include "vector.h"
#include "iterator.h"


typedef struct hash_map {
	size_t n_buckets;
	size_t(*hash_f)(const void*);	
	vector_t buckets;
	size_t size;
} hash_map_t;

typedef struct hash_map_query {
	int success;
	void* data;
} hash_map_query_t;


hash_map_t* hash_map_create(	
	size_t v_size,
	size_t n_buckets,
	size_t(*hash_f)(const void*)	
);

void hash_map_destroy(hash_map_t* h);

void hash_map_init(
	hash_map_t* h, 	
	size_t v_size, 
	size_t n_buckets, 
	size_t(*hash_f)(const void*)	
);

void hash_map_close(hash_map_t* h);

hash_map_query_t hash_map_contains(hash_map_t* h, const void* key);

hash_map_query_t hash_map_try_insert(hash_map_t* h, const void* key);

iterator_t hash_map_iterator(hash_map_t* h);

void* hash_map_insert(hash_map_t* h, const void* key);

void* hash_map_at(hash_map_t* h, const void* key);

void hash_map_erase(hash_map_t* h, const void* key);

void hash_map_clear(hash_map_t* h);

int hash_map_is_empty(hash_map_t* h);

size_t hash_map_size(hash_map_t* h);