#include "vector.h"
#include "iterator.h"
#include <stdlib.h>
#include <string.h>


void vector_init(vector_t *v, const size_t t_size, const size_t capacity) {
    v->data = malloc(t_size * capacity);
    v->capacity = capacity;
    v->t_size = t_size;
    v->size = 0;
}

void vector_close(vector_t* v) {
    free(v->data);
}


iterator_t vector_get_iterator(vector_t *v) {
    iterator_t i;
    i.begin = v->data;
    i.end = v->data + v->t_size * (v->size + 1);
    i.step = v->t_size;
    return i;
}


void vector_grow(vector_t *v) {
    v->data = realloc(v->data, v->capacity * 2);
    v->capacity *= 2;    
}


void* vector_allocate(vector_t* v) {
    if (v->size >= v->capacity) {
        vector_grow(v);
    }
    char* p; 
    p = v->data + v->t_size * v->size;
    v->size += 1;
    return p;
}


void* vector_at(vector_t* v, const size_t i) {
    return v->data + v->t_size * i;
}


void vector_erase(vector_t *v, const size_t i) {
    void* src = vector_at(v, v->size);
    void* dst = vector_at(v, i);
    memcpy(dst, src, v->t_size);
}


void vector_clear(vector_t *v) {
    v->size = 0;
}