#pragma once
#include "vector.h"
#include "util.h"
#include "vec_iterator.h"
#include "../constants.h"


typedef struct hash_set {
	vector_t* buckets;
	size_t(*hash)(const void*);
	int (*equal)(const void*, const void*);
	size_t v_size;
	size_t n_buckets;
	size_t size;
} hash_set_t;


void hash_set_init(
	hash_set_t* h,
	size_t v_size,
	size_t n_buckets,
	size_t(*hash)(const void*),
	int(*equal)(const void*, const void*)
);

void hash_set_entity_init(hash_set_t* h);

void hash_set_close(hash_set_t* h);

void hash_set_insert(hash_set_t* h, const void* data);

int hash_set_contains(hash_set_t* h, const void* data);

void hash_set_erase(hash_set_t* h, const void* data);

void hash_set_clear(hash_set_t* h);

vec_iterator_t hash_set_get_vec_iterator(hash_set_t* h);

int hash_set_is_empty(hash_set_t* h);

size_t hash_set_size(hash_set_t* h);