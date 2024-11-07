#include "hash_map.h"


void hash_map_init(
	hash_map_t* h,
	const size_t v_size,
	const size_t n_buckets,
	size_t(*hash)(const void*)
) {
	h->hash = hash;
	h->n_buckets = next_prime(n_buckets);
	h->v_size = v_size;
	h->size = 0;
	h->buckets = (vector_t*)malloc(sizeof(vector_t) * h->n_buckets);
	for (int i = 0; i < h->n_buckets; i++) {
		vector_init(h->buckets + i, sizeof(size_t) + v_size);
	}
}


void hash_map_close(hash_map_t* h) {
	for (vector_t* v = h->buckets; v < h->buckets + h->n_buckets; v++) {
		vector_close(v);
	}
	free(h->buckets);	
}


hash_map_query_t hash_map_allocate(hash_map_t* h, const void* key) {
	hash_map_query_t q = { 0, NULL };
	const size_t k = h->hash(key);	
	vector_t* vec = h->buckets + (k % h->n_buckets);
	const iterator_t iter = vector_iterator(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (k == *((size_t*)p)) {
			q.value = p + sizeof(size_t);
			return q;
		}
	}
	q.success = 1;
	char* new_pair = vector_allocate(vec);
	*((size_t*)new_pair) = k;
	q.value = new_pair + sizeof(size_t);
	h->size++;
	return q;
}


int hash_map_insert(hash_map_t* h, const void* key, const void* value) {
	const size_t k = h->hash(key);	
	vector_t* vec = h->buckets + (k % h->n_buckets);
	const iterator_t iter = vector_iterator(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (k == *((size_t*)p)) {
			return 0;
		}
	}
	char* new_pair = vector_allocate(vec);
	*((size_t*)new_pair) = k;
	memcpy(new_pair + sizeof(size_t), value, h->v_size);
	h->size++;
	return 1;
}


void hash_map_erase(hash_map_t* h, const void* key) {
	const size_t k = h->hash(key);	
	vector_t* vec = h->buckets + (k % h->n_buckets);	
	const iterator_t iter = vector_iterator(vec);
	size_t i = 0;
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (k == *((size_t*)p)) {
			vector_erase(vec, i);
			h->size--;
			return;
		}
		i++;
	}
}


void* hash_map_at(hash_map_t* h, const void* key) {
	const size_t k = h->hash(key);	
	vector_t* vec = h->buckets + (k % h->n_buckets);	
	const iterator_t iter = vector_iterator(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step)
		if (k == *((size_t*)p))
			return p + sizeof(size_t);
	return NULL;
}


hash_map_query_t hash_map_find(hash_map_t* h, const void* key) {
	hash_map_query_t q = { 0, NULL };
	const size_t k = h->hash(key);	
	vector_t* vec = h->buckets + (k % h->n_buckets);	
	const iterator_t iter = vector_iterator(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (k == *((size_t*)p)) {
			q.success = 1;
			q.value = p + sizeof(size_t);
			return q;
		}
	}
	return q;
}

vec_iterator_t hash_map_get_vec_iterator(hash_map_t* h) {
	const vec_iterator_t iter = { h->buckets, h->buckets + h->n_buckets };
	return iter;
}


void hash_map_clear(hash_map_t* h) {
	for (vector_t* v = h->buckets; v < h->buckets + h->n_buckets; v++) {
		vector_clear(v);
	}	
	h->size = 0;
}


int hash_map_is_empty(hash_map_t* h) {
	return h->size == 0;
}


size_t hash_map_size(hash_map_t* h) {
	return h->size;
}