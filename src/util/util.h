#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "types.h"

size_t hash_str(const void* s);

size_t hash_size_t(const void* k);

size_t hash_entity_t(const void* e);

int is_prime(size_t n);

size_t next_prime(size_t n);