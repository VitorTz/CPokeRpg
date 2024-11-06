#include "mstring.h"


void mstring_init(mstring_t* s) {
	vector_init(&s->arr, sizeof(char));
	vector_reserve(&s->arr, 16);
	*((char*)vector_allocate(&s->arr)) = '\0';
}


void mstring_close(mstring_t* s) {
	vector_close(&s->arr);
}


void mstring_append(mstring_t* s, const char* str) {	
	s->arr.size--;
	char c;
	while ((c = *str++)) {
		*((char*)vector_allocate(&s->arr)) = c;		
	}
	*((char*)vector_allocate(&s->arr)) = '\0';
}


const char* mstring_get_str(mstring_t* s) {
	return s->arr.data;
}


void mstring_clear(mstring_t* s) {
	vector_clear(&s->arr);
	*((char*)vector_allocate(&s->arr)) = '\0';
}


size_t mstring_lenght(mstring_t* s) {
	return s->arr.size - 1;
}

