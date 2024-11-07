#include "hash_map.h"


void hash_map_init(
	hash_map_t* h,
	const size_t v_size,
	size_t(*hash)(const void*)
) {
	vector_init(&h->buckets, sizeof(vector_t));
	vector_reserve(&h->buckets, 16);
	h->buckets.size = 16;
	const iterator_t iter = vector_iterator(&h->buckets);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_init(v, sizeof(size_t) + v_size);
	} 
	h->hash = hash;
	h->v_size = v_size;
	h->size = 0;
}


void hash_map_close(hash_map_t* h) {
	const iterator_t iter = vector_iterator(&h->buckets);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_close(v);
	}
	vector_close(&h->buckets);
}


void hash_map_reserve(hash_map_t* h, const size_t n) {
	if (n > h->buckets.size) {
		const size_t last_n = h->buckets.size;
		vector_reserve(&h->buckets, n);
		h->buckets.size = n;

		const iterator_t iter = vector_iterator(&h->buckets);
		vector_t* begin = ((vector_t*)iter.begin) + last_n;
		vector_t* end = (vector_t*)iter.end;
		for (vector_t* v = begin; v < end; v++) {
			vector_init(v, sizeof(size_t) + h->v_size);
		}
	}
}


hash_map_query_t hash_map_allocate(hash_map_t* h, const void* key) {
	hash_map_query_t q = { 0, NULL };
	const size_t k = h->hash(key);
	const size_t index = k % h->buckets.size;
	vector_t* vec = vector_at(&h->buckets, index);
	const iterator_t iter = vector_iterator(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (k == *((size_t*)p)) {
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
	const size_t index = k % h->buckets.size;
	vector_t* vec = vector_at(&h->buckets, index);
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
	const size_t index = k % h->buckets.size;
	vector_t* vec = vector_at(&h->buckets, index);
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
	const size_t index = k % h->buckets.size;
	vector_t* vec = vector_at(&h->buckets, index);
	const iterator_t iter = vector_iterator(vec);

	for (char* p = iter.begin; p < iter.end; p += iter.step)
		if (k == *((size_t*)p))
			return p + sizeof(size_t);
	return NULL;
}


hash_map_query_t hash_map_find(hash_map_t* h, const void* key) {
	hash_map_query_t q = { 0, NULL };
	const size_t k = h->hash(key);
	const size_t index = k % h->buckets.size;
	vector_t* vec = vector_at(&h->buckets, index);
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