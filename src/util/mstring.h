#pragma once
#include "vector.h"


typedef struct mstring {
	vector_t arr;	
} mstring_t;


void mstring_init(mstring_t* s);

void mstring_close(mstring_t* s);

const char* mstring_get_str(mstring_t* s);

void mstring_append(mstring_t* s, const char* str);

void mstring_clear(mstring_t* s);

size_t mstring_lenght(mstring_t* s);