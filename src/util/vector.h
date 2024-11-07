#pragma once
#include <stdlib.h>
#include <string.h>
#include "iterator.h"


typedef struct vector {
	size_t t_size;
	size_t size;
	size_t capacity;
	char* data;
} vector_t;


void vector_init(vector_t* v, size_t t_size);

void vector_close(vector_t* v);

void vector_reserve(vector_t* v, size_t n);

void vector_grow(vector_t* v);

iterator_t vector_iterator(vector_t* v);

void vector_push_back(vector_t* v, const void* data);

void* vector_allocate(vector_t* v);

void* vector_begin(vector_t* v);

void* vector_end(vector_t* v);

void* vector_at(vector_t* v, size_t i);

void vector_set(vector_t* v, size_t i, const void* data);

void vector_insert(vector_t* v, size_t i, const void* data);

void vector_erase(vector_t* v, size_t i);

void vector_clear(vector_t* v);

void vector_pop(vector_t* v, size_t i, void* r);

void vector_pop_back(vector_t* v, void* r);

void vector_pop_front(vector_t* v, void* r);

const void* vector_back(vector_t* v);

const void* vector_front(vector_t* v);

size_t vector_size(vector_t* v);
