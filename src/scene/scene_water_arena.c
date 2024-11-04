#include "scene.h"
#include "scene_id.h"


void scene_water_arena_init() {
    scene_init(WaterArenaSceneID);
}


void scene_water_arena_update(const float dt) {
    scene_update(dt, WaterArenaSceneID);
}


void scene_water_arena_draw() {
    scene_draw(WaterArenaSceneID);
}