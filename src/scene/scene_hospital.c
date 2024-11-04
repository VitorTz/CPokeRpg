#include "scene.h"
#include "scene_id.h"


void scene_hospital_init() {
    scene_init(HospitalSceneID);
}


void scene_hospital_update(const float dt) {
    scene_update(dt, HospitalSceneID);
}


void scene_hospital_draw() {
    scene_draw(HospitalSceneID);
}