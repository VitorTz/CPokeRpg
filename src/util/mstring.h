#pragma once
#include "vector.h"

typedef vector_t string_t;

void string_init(string_t* str);

void string_close(string_t* str);

void string_append(string_t* str, const char* s);

char string_at(string_t* str, size_t i);

const char* string_get(string_t* str);

void string_clear(string_t* str);

iterator_t string_iterator(string_t* str);

size_t string_lenght(string_t* str);



