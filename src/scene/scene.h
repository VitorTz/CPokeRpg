#ifndef PK_SCENE_H
#define PK_SCENE_H
#include "scene_id.h"


typedef struct scene_manager {
    SceneId current_scene;
    SceneId next_scene;
    int should_change_scene;
} scene_manager_t;


void scene_init(SceneId scene_id);
void scene_update(float dt, SceneId scene_id);
void scene_draw(SceneId scene_id);


void scene_title_screen_init();
void scene_title_screen_update(float dt);
void scene_title_screen_draw();


void scene_world_init();
void scene_world_update(float dt);
void scene_world_draw();


void scene_fire_arena_init();
void scene_fire_arena_update(float dt);
void scene_fire_arena_draw();


void scene_plant_arena_init();
void scene_plant_arena_update(float dt);
void scene_plant_arena_draw();


void scene_water_arena_init();
void scene_water_arena_update(float dt);
void scene_water_arena_draw();


void scene_hospital_init();
void scene_hospital_update(float dt);
void scene_hospital_draw();


void scene_house_init();
void scene_house_update(float dt);
void scene_house_draw();


void scene_manager_init();
void scene_manager_load_next_scene();
void scene_manager_change_scene(SceneId scene_id);
void scene_manager_update(float dt);
void scene_manager_draw();


#endif