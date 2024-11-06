#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "iterator.h"


typedef struct vector {
	size_t size;
	size_t t_size;
	size_t capacity;
	char* data;
} vector_t;

void vector_init(vector_t* v, size_t t_size);

void vector_reserve(vector_t* v, size_t capacity);

void vector_close(vector_t* v);

iterator_t vector_iterator(vector_t* v);

void* vector_allocate(vector_t* v);

void vector_grow(vector_t* v);

void* vector_front(vector_t* v);

void* vector_back(vector_t* v);

void* vector_at(vector_t* v, size_t i);

int vector_is_empty(vector_t* v);

void vector_clear(vector_t* v);

void vector_erase(vector_t* v, size_t i);

size_t vector_size(vector_t* v);
