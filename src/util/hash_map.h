#pragma once
#include "iterator.h"
#include "vector.h"
#include "util.h"


typedef struct hash_map {
	vector_t buckets;
	size_t(*hash)(const void*);	
	size_t v_size;
	size_t size;
} hash_map_t;


typedef struct hash_map_query {
	int success;
	void* value;
} hash_map_query_t;


void hash_map_init(
	hash_map_t* h,
	size_t v_size,	
	size_t(*hash)(const void*)
);


void hash_map_close(hash_map_t* h);

void hash_map_reserve(hash_map_t* h, size_t n);

hash_map_query_t hash_map_allocate(hash_map_t* h, const void* key);

int hash_map_insert(hash_map_t* h, const void* key, const void* value);

void hash_map_erase(hash_map_t* h, const void* key);

void* hash_map_at(hash_map_t* h, const void* key);

hash_map_query_t hash_map_find(hash_map_t* h, const void* key);

void hash_map_clear(hash_map_t* h);

int hash_map_is_empty(hash_map_t* h);

size_t hash_map_size(hash_map_t* h);