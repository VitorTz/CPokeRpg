#include "hash_map.h"


void hash_map_init(
	hash_map_t* h,	
	const size_t v_size,
	const size_t n_buckets,
	size_t(*hash_f)(const void*)	
) {
	h->n_buckets = n_buckets;
	h->hash_f = hash_f;	
	h->size = 0;
	vector_init(&h->buckets, sizeof(vector_t));
	vector_reserve(&h->buckets, n_buckets);
	h->buckets.size = n_buckets;
	iterator_t iter = vector_iterator(&h->buckets);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_init(v, sizeof(size_t) + v_size);
	}
}

hash_map_t* hash_map_create(	
	const size_t v_size,
	const size_t n_buckets,
	size_t(*hash_f)(const void*)
) {
	hash_map_t* h = (hash_map_t*)malloc(sizeof(hash_map_t));
	hash_map_init(h, v_size, n_buckets, hash_f);
	return h;
}

void hash_map_destroy(hash_map_t* h) {
	hash_map_close(h);
	free(h);
}


void hash_map_close(hash_map_t* h) {
	iterator_t iter = vector_iterator(&h->buckets);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_close(v);
	}
}


hash_map_query_t hash_map_contains(hash_map_t* h, const void* key) {	
	hash_map_query_t q = { 0, NULL };
	const size_t k1 = h->hash_f(key);

	vector_t* v = (vector_t*)vector_at(&h->buckets, k1 % h->n_buckets);
	iterator_t iter = vector_iterator(v);

	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		const size_t* k2 = (size_t*) p;
		if (*k2 == k1) {
			q.success = 1;
			q.data = p + sizeof(size_t);
			break;
		}
	}
	return q;
}


hash_map_query_t hash_map_try_insert(hash_map_t* h, const void* key) {
	hash_map_query_t q = { 1, NULL };
	const size_t k1 = h->hash_f(key);

	vector_t* v = (vector_t*)vector_at(&h->buckets, k1 % h->n_buckets);
	const iterator_t iter = vector_iterator(v);

	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		const size_t* k2 = (size_t*)p;
		if (*k2 == k1) {
			q.success = 0;
			q.data = p + sizeof(size_t);
			return q;
		}
	}
	char* new_pair = (char*) vector_allocate(v);
	*((size_t*)new_pair) = k1;	
	q.data = new_pair + sizeof(size_t);
	h->size++;
	return q;
}


iterator_t hash_map_iterator(hash_map_t* h) {
	const iterator_t iter = vector_iterator(&h->buckets);
	return iter;
}


void* hash_map_insert(hash_map_t* h, const void* key) {
	const size_t k1 = h->hash_f(key);
	vector_t* v = (vector_t*)vector_at(&h->buckets, k1 % h->n_buckets);
	const iterator_t iter = vector_iterator(v);

	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		const size_t* k2 = (size_t*)p;
		if (*k2 == k1) {
			return p + sizeof(size_t);
		}
	}
	h->size++;
	char* new_pair = (char*)vector_allocate(v);
	*((size_t*)new_pair) = k1;
	return new_pair + sizeof(size_t);
}


void* hash_map_at(hash_map_t* h, const void* key) {
	const size_t k1 = h->hash_f(key);
	vector_t* v = (vector_t*)vector_at(&h->buckets, k1 % h->n_buckets);
	const iterator_t iter = vector_iterator(v);

	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		const size_t* k2 = (size_t*)p;
		if (*k2 == k1) {
			return p + sizeof(size_t);
		}
	}
	return NULL;
}


void hash_map_erase(hash_map_t* h, const void* key) {
	const size_t k1 = h->hash_f(key);
	vector_t* v = (vector_t*)vector_at(&h->buckets, k1 % h->n_buckets);
	const iterator_t iter = vector_iterator(v);

	size_t i = 0;
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		const size_t* k2 = (size_t*)p;
		if (*k2 == k1) {
			vector_erase(v, i);
			h->size--;
			return;
		}
		i++;
	}
}


void hash_map_clear(hash_map_t* h) {
	const iterator_t iter = vector_iterator(&h->buckets);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
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