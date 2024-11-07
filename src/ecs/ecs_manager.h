#pragma once
#include "ecs_instance.h"
#include "../util/util.h"
#include "../util/hash_map.h"
#include "../scene/scene_id.h"


typedef struct ecs_manager {
	hash_map_t ecs_map;
	ecs_instance_t* ecs;
} ecs_manager_t;


void ecs_manager_init();

void ecs_manager_close();

void ecs_manager_create_ecs(scene_id_t scene_id);

void ecs_manager_destroy_ecs(scene_id_t scene_id);

void ecs_manager_set_current_instance(scene_id_t scene_id);

ecs_instance_t* ecs_manager_get_ecs();

