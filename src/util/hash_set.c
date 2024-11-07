#include "hash_set.h"


void hash_set_init(
	hash_set_t* h,
	const size_t v_size,
	const size_t n_buckets,
	size_t(*hash)(const void*),
	int(*equal)(const void*, const void*)
) {
	h->hash = hash;
	h->equal = equal;
	h->n_buckets = next_prime(n_buckets);
	h->v_size = v_size;
	h->size = 0;
	h->buckets = (vector_t*)malloc(sizeof(vector_t) * h->n_buckets);
	for (vector_t* v = h->buckets; v < h->buckets + h->n_buckets; v++) {
		vector_init(v, v_size);
	}
}


void hash_set_entity_init(hash_set_t* h) {
	hash_set_init(
		h,
		sizeof(entity_t),
		MAX_ENTITIES / 4,
		hash_entity_t,
		equal_entity_t
	);
}


void hash_set_close(hash_set_t* h) {
	const vec_iterator_t iter = hash_set_get_vec_iterator(h);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_close(v);
	}	
	free(h->buckets);
}


void hash_set_insert(hash_set_t* h, const void* data) {
	const size_t k = h->hash(data);	
	vector_t* v = h->buckets + (k % h->n_buckets);	
	const iterator_t iter = vector_iterator(v);
	for (char* p = iter.begin; p < iter.end; p += iter.step)
		if (h->equal(p, data))
			return;
	vector_push_back(v, data);
	h->size++;
}


int hash_set_contains(hash_set_t* h, const void* data) {
	const size_t k = h->hash(data);
	vector_t* v = h->buckets + (k % h->n_buckets);
	const iterator_t iter = vector_iterator(v);	
	for (char* p = iter.begin; p < iter.end; p += iter.step)
		if (h->equal(p, data))
			return 1;
	return 0;
}


void hash_set_erase(hash_set_t* h, const void* data) {
	const size_t k = h->hash(data);
	vector_t* v = h->buckets + (k % h->n_buckets);
	const iterator_t iter = vector_iterator(v);
	size_t i = 0;
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (h->equal(p, data)) {
			vector_erase(v, i);
			h->size--;
			return;
		}
		i++;
	}
}

vec_iterator_t hash_set_get_vec_iterator(hash_set_t* h) {
	const vec_iterator_t iter = { h->buckets, h->buckets + h->n_buckets };
	return iter;
}


void hash_set_clear(hash_set_t* h) {
	for (vector_t* v = h->buckets; v < h->buckets + h->n_buckets; v++) {
		vector_clear(v);
	}
	h->size = 0;
}


int hash_set_is_empty(hash_set_t* h) {
	return h->size == 0;
}


size_t hash_set_size(hash_set_t* h) {
	return h->size;
}
