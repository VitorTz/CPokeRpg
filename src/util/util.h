#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../scene/scene_id.h"
#include "mstring.h"
#include "vector.h"
#include "types.h"


size_t hash_str(const void* s);

size_t hash_size_t(const void* k);

size_t hash_entity_t(const void* e);

size_t hash_zindex(const void* z);

size_t hash_component_t(const void* data);

size_t hash_scene_id(const void* data);

int equal_component_t(const void* l, const void* r);

int equal_entity_t(const void* l, const void* r);

int is_prime(size_t n);

size_t next_prime(size_t n);

void random_file_from_dir(const char* dir, string_t* str);

double dclamp(double d, double min, double max);

float fclamp(float d, float min, float max);