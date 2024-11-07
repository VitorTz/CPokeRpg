#include "vector.h"


void vector_init(vector_t* v, size_t t_size) {
	v->t_size = t_size;
	v->size = 0;
	v->capacity = 4;
	v->data = (char*)malloc(t_size * v->capacity);
}


void vector_close(vector_t* v) {
	free(v->data);
}


void vector_reserve(vector_t* v, const size_t n) {
	if (n > v->capacity) {
		void* tmp = realloc(v->data, (n + 1) * v->t_size);
		if (tmp != NULL) {
			v->data = tmp;
			v->capacity = n + 1;
		}
	}
}


void vector_grow(vector_t* v) {
	vector_reserve(v, v->capacity * 2);
}


iterator_t vector_iterator(vector_t* v) {
	const iterator_t iter = { v->data, v->data + v->t_size * v->size, v->t_size};
	return iter;
}


void vector_push_back(vector_t* v, const void* data) {
	if (v->size >= v->capacity) {
		vector_grow(v);
	}
	memcpy(v->data + v->t_size * v->size, data, v->t_size);
	v->size++;
}


void* vector_allocate(vector_t* v) {
	if (v->size >= v->capacity) {
		vector_grow(v);
	}
	void* p = v->data + v->t_size * v->size;
	v->size++;
	return p;
}


void* vector_begin(vector_t* v) {
	return v->data;
}


void* vector_end(vector_t* v) {
	return v->data + v->t_size * v->size;
}


void* vector_at(vector_t* v, const size_t i) {	
	return v->data + v->t_size * i;
}


void vector_set(vector_t* v, const size_t i, const void* data) {	
	memcpy(v->data + v->t_size * i, data, v->t_size);
}


void vector_insert(vector_t* v, const size_t i, const void* data) {
	if (v->size >= v->capacity) {
		vector_grow(v);
	}
	// Move to right
	char* begin = v->data + v->t_size * (v->size - 1);	
	char* end = v->data + v->t_size * i;
	for (char* p = begin; p >= end; p -= v->t_size) {
		memcpy(p + v->t_size, p, v->t_size);
	}	
	memcpy(end, data, v->t_size);	
}


void vector_erase(vector_t* v, const size_t i) {
	// Copy the last item in the removed item
	memcpy(
		v->data + v->t_size * i, 
		v->data + v->t_size * (v->size - 1), 
		v->t_size
	);
	v->size--;
}


void vector_clear(vector_t* v) {
	v->size = 0;
}


void vector_pop(vector_t* v, const size_t i, void* r) {	
	memcpy(r, v->data + v->t_size * i, v->t_size);
	vector_erase(v, i);
}


void vector_pop_back(vector_t* v, void* r) {
	memcpy(r, v->data + v->t_size * (v->size - 1), v->t_size);
	v->size--;	
}


void vector_pop_front(vector_t* v, void* r) {
	memcpy(r, v->data, v->t_size);
	vector_erase(v, 0);
}


void vector_swap(vector_t* v, const size_t a, const size_t b) {
	// Copy a to last item
	memcpy(v->data + v->t_size * (v->size + 1), v->data + v->t_size * a, v->t_size);
	// Copy b to a
	memcpy(v->data + v->t_size * a, v->data + v->t_size * b, v->t_size);
	// Copy a to b
	memcpy(v->data + v->t_size * b, v->data + v->t_size * (v->size + 1), v->t_size);
}


const void* vector_back(vector_t* v) {
	return v->data + v->t_size * (v->size - 1);	
}


const void* vector_front(vector_t* v) {
	return v->data;
}


int vector_is_empty(vector_t* v) {
	return v->size == 0;
}


size_t vector_size(vector_t* v) {
	return v->size;
}