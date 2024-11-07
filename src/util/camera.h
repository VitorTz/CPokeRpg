#pragma once
#include <raylib.h>
#include "vector.h"
#include "hash_map.h"
#include "util.h"
#include "../ecs/system_manager.h"
#include "../constants.h"



typedef struct camera {
	hash_map_t zindex_to_entities;
	Camera2D camera2D;
	size_t size;
	char is_on_camera[MAX_ENTITIES];
} camera_t;


void camera_init(camera_t* c);

void camera_close(camera_t* c);

void camera_insert(camera_t* c, entity_t e, zindex_t zindex);

void camera_erase(camera_t* c, entity_t e, zindex_t zindex);

void camera_add_zoom(camera_t* c, float zoom);

void camera_set_zoom(camera_t* c, float zoom);

void camera_set_target(camera_t* c, Vector2 target);

void camera_draw(camera_t* c, system_manager_t* system_manager);

void camera_clear(camera_t* c);

size_t camera_num_entities(camera_t* c);

