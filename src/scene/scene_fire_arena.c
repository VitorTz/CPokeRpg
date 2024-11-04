#include "scene.h"
#include "scene_id.h"


void scene_fire_arena_init() {
    scene_init(FireArenaSceneID);
}


void scene_fire_arena_update(const float dt) {
    scene_update(dt, FireArenaSceneID);
}


void scene_fire_arena_draw() {
    scene_draw(FireArenaSceneID);
}