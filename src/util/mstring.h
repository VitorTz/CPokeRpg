#pragma once
#include "vector.h"


typedef struct string {
	size_t size;
	size_t capacity;
	char* data;
} string_t;

void string_init(string_t* str);

void string_close(string_t* str);

void string_append(string_t* str, const char* s);

const char* string_get(string_t* str);

void string_clear(string_t* str);

size_t string_lenght(string_t* str);



