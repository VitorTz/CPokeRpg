#ifndef PK_ITERATOR_H
#define PK_ITERATOR_H
#include <stddef.h>


typedef struct iterator {
    char* begin;
    char* end;
    size_t step;
} iterator_t;


#endif