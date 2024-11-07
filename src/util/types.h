#pragma once
#include <stdint.h>


typedef uint32_t entity_t;
typedef uint8_t component_t;
typedef uint8_t zindex_t;

typedef struct entity_pair {
	entity_t e;
	float y_pos;
} entity_pair_t;