#include "mstring.h"


static char END_STR = '\0';


void string_init(string_t* str) {
	str->capacity = 16;
	str->size = 0;
	str->data = (char*) malloc(sizeof(char) * str->capacity);
	str->data = '\0';
}


void string_close(string_t* str) {
	free(str->data);	
}


void string_append(string_t* str, const char* s) {
	const size_t len = strlen(s);
	if (str->size + len >= str->capacity) {
		void* tmp = realloc(str->data, str->size + (len * 2));
		if (tmp != NULL) {
			str->data = tmp;
			str->capacity = str->size + (len * 2);
		}
	}
	char c;	
	while ((c = *s++)) {
		*(str->data + str->size++) = c;
	}
	*(str->data + str->size) = '\0';
}


const char* string_get(string_t* str) {
	return str->data;
}


void string_clear(string_t* str) {
	str->size = 0;
	str->data = '\0';
}


size_t string_lenght(string_t* str) {
	return str->size - 1;
}