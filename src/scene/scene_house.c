#include "scene.h"
#include "scene_id.h"


void scene_house_init() {
    scene_init(HouseSceneID);
}


void scene_house_update(const float dt) {
    scene_update(dt, HouseSceneID);
}


void scene_house_draw() {
    scene_draw(HouseSceneID);
}