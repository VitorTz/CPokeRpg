#pragma once
#include <string>
#include "../util/mstring.h"
#include "assert.h"


void test_string_append() {
	std::string test_str = "13123213131231231231312";
	const char* c_test_str = test_str.c_str();
	string_t str;
	string_init(&str);	
	string_append(&str, c_test_str);
	
	for (int i = 0; i < string_lenght(&str); i++) {
		char a = string_at(&str, i);
		char b = test_str.at(i);
		assert(a == b);
	}
	string_close(&str);
}


void test_string_get() {
	std::string test_str = "13123213131231231231312";
	const char* c_test_str = test_str.c_str();
	string_t str;
	string_init(&str);
	string_append(&str, c_test_str);
	const char* s_str = string_get(&str);
	assert(*c_test_str == *s_str);
	string_close(&str);
}