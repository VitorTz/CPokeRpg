#pragma once
#include "components.h"
#include "../util/vector.h"
#include "../util/vector_entity.h"
#include "../util/types.h"


typedef struct system {
	void (*update)(const float dt, vector_t*);
	void (*draw)(const entity_t e);
} system_t;


typedef struct system_manager {
	system_t* systems;	
} system_manager_t;


void system_manager_init(system_manager_t* s_manager);

void system_manager_close(system_manager_t* s_manager);

void system_manager_update(float dt);

void system_manager_draw(vector_entity_t* vec);

