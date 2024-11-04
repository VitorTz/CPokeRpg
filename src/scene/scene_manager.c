#include "scene.h"
#include "../constants.h"
#include "scene_id.h"


static scene_manager_t m_scene_manager;


void scene_manager_init() {
    m_scene_manager.current_scene = MAIN_SCENE;
    m_scene_manager.next_scene = MAIN_SCENE;
    m_scene_manager.should_change_scene = 0;    
}


void scene_manager_load_next_scene() {
    switch (m_scene_manager.next_scene) {
        case TitleScreenID:
            scene_title_screen_init();
            break;
        case WorldSceneSceneID:
            scene_world_init();
            break;
        case FireArenaSceneID:
            scene_fire_arena_init();
            break;
        case PlantArenaSceneID:
            scene_plant_arena_init();
            break;
        case WaterArenaSceneID:
            scene_water_arena_init();
            break;
        case HospitalSceneID:
            scene_hospital_init();
            break;
        case HouseSceneID:
            scene_hospital_init();
            break;
        default:
            break;
    }
    m_scene_manager.current_scene = m_scene_manager.next_scene;
}


void scene_manager_change_scene(const SceneId scene_id) {
    m_scene_manager.should_change_scene = 1;
    m_scene_manager.next_scene = scene_id;
}


void scene_manager_update(const float dt) {
    switch (m_scene_manager.current_scene) {
        case TitleScreenID:
            scene_title_screen_update(dt);
            break;
        case WorldSceneSceneID:
            scene_world_update(dt);
            break;
        case FireArenaSceneID:
            scene_fire_arena_update(dt);
            break;
        case PlantArenaSceneID:
            scene_plant_arena_update(dt);
            break;
        case WaterArenaSceneID:
            scene_water_arena_update(dt);
            break;
        case HospitalSceneID:
            scene_hospital_update(dt);
            break;
        case HouseSceneID:
            scene_hospital_update(dt);
            break;
        default:
            break;
    }
    if (m_scene_manager.should_change_scene) {
        m_scene_manager.should_change_scene = 0;
        scene_manager_load_next_scene();
    }
}


void scene_manager_draw() {
    switch (m_scene_manager.current_scene) {
        case TitleScreenID:
            scene_title_screen_draw();
            break;
        case WorldSceneSceneID:
            scene_world_draw();
            break;
        case FireArenaSceneID:
            scene_fire_arena_draw();
            break;
        case PlantArenaSceneID:
            scene_plant_arena_draw();
            break;
        case WaterArenaSceneID:
            scene_water_arena_draw();
            break;
        case HospitalSceneID:
            scene_hospital_draw();
            break;
        case HouseSceneID:
            scene_hospital_draw();
            break;
        default:
            break;
    }
}
