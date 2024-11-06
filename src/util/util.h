#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "mstring.h"

size_t hash_str(const void* s);

size_t hash_size_t(const void* k);

size_t hash_entity_t(const void* e);

void random_file_from_dir(const char* dir, mstring_t* result);