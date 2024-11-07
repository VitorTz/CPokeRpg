#include "mstring.h"


static char END_STR = '\0';


void string_init(string_t* str) {
	vector_init(str, sizeof(char));
	vector_push_back(str, &END_STR);
}


void string_close(string_t* str) {
	vector_close(str);
}


void string_append(string_t* str, const char* s) {
	char c;
	str->size--;
	while ((c = *s++)) {
		vector_push_back(str, &c);
	}
	vector_push_back(str, &END_STR);
}


char string_at(string_t* str, const size_t i) {
	const char c = *((char*)vector_at(str, i));
	return c;
}


const char* string_get(string_t* str) {
	return str->data;
}


iterator_t string_iterator(string_t* str) {
	return vector_iterator(str);
}


void string_clear(string_t* str) {
	vector_close(str);
}


size_t string_lenght(string_t* str) {
	return str->size - 1;
}