#include "scene.h"
#include "scene_id.h"


void scene_plant_arena_init() {
    scene_init(PlantArenaSceneID);
}


void scene_plant_arena_update(const float dt) {
    scene_update(dt, PlantArenaSceneID);
}


void scene_plant_arena_draw() {
    scene_draw(PlantArenaSceneID);
}