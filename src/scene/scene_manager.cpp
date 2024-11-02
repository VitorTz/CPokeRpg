#include "scene.h"


static pk::scene_manager_t mscene_manager{};


void pk::scene_manager_init() {	
	pk::scene_manager_load_next_scene();
}


void pk::scene_manager_load_next_scene() {	
	switch (mscene_manager.nextSceneId) {
		case pk::TitleScreenID:
			pk::scene_title_screen_init();
			break;
		case pk::WorldSceneID:
			pk::scene_world_init();
			break;
		case pk::FireArenaSceneID:
			pk::scene_fire_arena_init();
			break;
		case pk::PlantArenaSceneID:
			pk::scene_plant_arena_init();
			break;
		case pk::WaterArenaSceneID:
			pk::scene_water_arena_init();
			break;
		case pk::HospitalArenaSceneID:
			pk::scene_hospital_init();
			break;
		case pk::HouseSceneID:
			pk::scene_house_init();
			break;
		default:
			break;
	}
	mscene_manager.currentSceneId = mscene_manager.nextSceneId;
}


void pk::scene_manager_change_scene(const pk::SceneID sceneId) {
	mscene_manager.shouldChangeScene = true;
	mscene_manager.nextSceneId = sceneId;
}


void pk::scene_manager_update(const float dt) {
	switch (mscene_manager.nextSceneId) {
		case pk::TitleScreenID:
			pk::scene_title_screen_update(dt);
			break;
		case pk::WorldSceneID:
			pk::scene_world_update(dt);
			break;
		case pk::FireArenaSceneID:
			pk::scene_fire_arena_update(dt);
			break;
		case pk::PlantArenaSceneID:
			pk::scene_plant_arena_update(dt);
			break;
		case pk::WaterArenaSceneID:
			pk::scene_water_arena_update(dt);
			break;
		case pk::HospitalArenaSceneID:
			pk::scene_hospital_update(dt);
			break;
		case pk::HouseSceneID:
			pk::scene_house_update(dt);
			break;
		default:
			break;
	}
}


void pk::scene_manager_draw() {
	switch (mscene_manager.nextSceneId) {
		case pk::TitleScreenID:
			pk::scene_title_screen_draw();
			break;
		case pk::WorldSceneID:
			pk::scene_world_draw();
			break;
		case pk::FireArenaSceneID:
			pk::scene_fire_arena_draw();
			break;
		case pk::PlantArenaSceneID:
			pk::scene_plant_arena_draw();
			break;
		case pk::WaterArenaSceneID:
			pk::scene_water_arena_draw();
			break;
		case pk::HospitalArenaSceneID:
			pk::scene_hospital_draw();
			break;
		case pk::HouseSceneID:
			pk::scene_house_draw();
			break;
		default:
			break;
	}
}