#pragma once
#include <stdlib.h>
#include "scene_id.h"
#include "../util/image.h"
#include "../util/util.h"
#include "../constants.h"

typedef struct scene {
	scene_id_t id;
	void (*init)(scene_id_t);
	void (*update)(scene_id_t, float);
	void (*draw)(scene_id_t);
} scene_t;


typedef struct scene_manager {
	scene_t* scenes;
	scene_id_t current_scene_id;
	scene_id_t next_scene_id;
	int should_change_scene;	
} scene_manager_t;


void scene_manager_init();
void scene_manager_close();
scene_t* scene_manager_get_scene(scene_id_t scene_id);
void scene_manager_load_next_scene();
void scene_manager_change_scene(const scene_id_t scene_id);
void scene_manager_update(float dt);
void scene_manager_draw();