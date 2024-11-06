#include "vector.h"


void vector_init(vector_t* v, const size_t t_size) {
	v->capacity = 8;
	v->t_size = t_size;
	v->size = 0;
	v->data = (char*)malloc(t_size * v->capacity);
}


void vector_close(vector_t* v) {
	free(v->data);
}


void vector_reserve(vector_t* v, const size_t capacity) {
	void* tmp = realloc(v->data, capacity * v->t_size);
	if (tmp != NULL) {
		v->data = tmp;
		v->capacity = capacity;
	}
}


void vector_grow(vector_t* v) {
	void* tmp = realloc(v->data, v->capacity * 2 * v->t_size);
	if (tmp != NULL) {
		v->data = tmp;
		v->capacity *= 2;
	}
}


void* vector_allocate(vector_t* v) {
	if (v->size >= v->capacity) {
		vector_grow(v);
	}
	v->size++;
	return vector_at(v, v->size - 1);
}


void* vector_at(vector_t* v, const size_t i) {
	void* p = (char*)v->data + v->t_size * i;
	return p;
}


void* vector_front(vector_t* v) {
	return vector_at(v, 0);
}


void* vector_back(vector_t* v) {
	return vector_at(v, v->size - 1);
}


int vector_is_empty(vector_t* v) {
	return v->size == 0;
}


iterator_t vector_iterator(vector_t* v) {
	iterator_t iter = { 
		v->data, 
		(char*)v->data + v->t_size * v->size,
		v->t_size
	};
	return iter;
}


void vector_erase(vector_t* v, const size_t i) {
	void* dst = vector_at(v, i);
	const void* src = vector_back(v);
	memcpy(dst, src, v->t_size);
	v->size--;
}


void vector_clear(vector_t* v) {
	v->size = 0;
}


size_t vector_size(vector_t* v) {
	return v->size;
}