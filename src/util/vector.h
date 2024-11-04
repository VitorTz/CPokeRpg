#ifndef PK_VECTOR_H
#define PK_VECTOR_H
#include <stddef.h>
#include "iterator.h"


typedef struct vector {
    size_t t_size;
    size_t size;
    size_t capacity;
    char* data;
} vector_t;


void vector_init(vector_t* v, size_t t_size, size_t capacity);

void vector_close(vector_t* v);

void vector_grow(vector_t* v);

iterator_t vector_get_iterator(vector_t* v);

void* vector_allocate(vector_t* v);

void* vector_at(vector_t* v, size_t i);

void vector_erase(vector_t* v, size_t i);

void vector_clear(vector_t* v);


#endif