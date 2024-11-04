#include "scene.h"
#include "scene_id.h"


void scene_world_init() {
    scene_init(WorldSceneSceneID);
}


void scene_world_update(const float dt) {
    scene_update(dt, WorldSceneSceneID);
}


void scene_world_draw() {
    scene_draw(WorldSceneSceneID);
}