#pragma once
#include "scene.h"
#include "../util/image.h"
#include "../util/util.h"


void scene_title_screen_init(scene_id_t scene_d);
void scene_title_screen_update(scene_id_t scene_d, float dt);
void scene_title_screen_draw(scene_id_t scene_d, float dt);