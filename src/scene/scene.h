#pragma once
#include "../constants.h"
#include "../util/sceneid.h"


namespace pk {

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

	typedef struct scene_manager {
		pk::SceneID currentSceneId{pk::MAIN_SCENE};
		pk::SceneID nextSceneId{pk::MAIN_SCENE};
		bool shouldChangeScene{};		
	} scene_manager_t;

	void scene_manager_init();
	void scene_manager_load_next_scene();
	void scene_manager_change_scene(pk::SceneID sceneId);
	void scene_manager_update(float dt);
	void scene_manager_draw();	

}