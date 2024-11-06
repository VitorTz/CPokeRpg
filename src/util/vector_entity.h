#pragma once
#include "vector.h"
#include "types.h"
#include "../constants.h"


typedef struct entity_pair {
	float y;
	entity_t e;
} entity_pair_t;

typedef struct vector_entity {
	vector_t* vec;
} vector_entity_t;

void vector_entity_init(vector_entity_t* vec);

void vector_entity_close(vector_entity_t* vec);

void vector_entity_push_back(vector_entity_t* vec, entity_pair_t* pair);

void vector_entity_clear(vector_entity_t* vec);

iterator_t vector_entity_iterator(vector_entity_t* vec);

