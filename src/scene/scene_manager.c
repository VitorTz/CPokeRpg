#include "scene.h"
#include "scene_title_screen.h"
#include "scene_world.h"
#include "scene_fire_arena.h"
#include "scene_water_arena.h"
#include "scene_plant_arena.h"
#include "scene_hospital.h"
#include "scene_house.h"
#include "scene_test.h"


static scene_manager_t m_scene_manager;


void scene_manager_init() {
	m_scene_manager.current_scene_id = MAIN_SCENE;
	m_scene_manager.next_scene_id = MAIN_SCENE;
	m_scene_manager.should_change_scene = 0;
	m_scene_manager.scenes = (scene_t*) malloc(sizeof(scene_t) * NumScenes);	

	scene_t* aux;

	// TitleScreen
	aux = scene_manager_get_scene(TitleScreenID);	
	aux->init = scene_title_screen_init;
	aux->update = scene_title_screen_update;
	aux->draw = scene_title_screen_draw;

	// World
	aux = scene_manager_get_scene(WorldSceneID);	
	aux->init = scene_world_init;
	aux->update = scene_world_update;
	aux->draw = scene_world_draw;

	// Fire Arena
	aux = scene_manager_get_scene(FireArenaSceneID);	
	aux->init = scene_fire_arena_init;
	aux->update = scene_fire_arena_update;
	aux->draw = scene_fire_arena_draw;

	// Water Arena
	aux = scene_manager_get_scene(WaterArenaSceneID);	
	aux->init = scene_water_arena_init;
	aux->update = scene_water_arena_update;
	aux->draw = scene_water_arena_draw;

	// Plant Arena
	aux = scene_manager_get_scene(PlantArenaSceneID);	
	aux->init = scene_plant_arena_init;
	aux->update = scene_plant_arena_update;
	aux->draw = scene_plant_arena_draw;

	// Hospital
	aux = scene_manager_get_scene(HospitalSceneID);	
	aux->init = scene_hospital_init;
	aux->update = scene_hospital_update;
	aux->draw = scene_hospital_draw;

	// House
	aux = scene_manager_get_scene(HouseSceneID);	
	aux->init = scene_house_init;
	aux->update = scene_house_update;
	aux->draw = scene_house_draw;

	// Test Scene
	aux = scene_manager_get_scene(TestSceneID);	
	aux->init = scene_test_init;
	aux->update = scene_test_update;
	aux->draw = scene_test_draw;

	scene_manager_load_next_scene();
}


void scene_manager_load_next_scene() {
	scene_t* scene = scene_manager_get_scene(m_scene_manager.next_scene_id);
	scene->init();
	m_scene_manager.current_scene_id = m_scene_manager.next_scene_id;
	m_scene_manager.should_change_scene = 0;
}


void scene_manager_close() {
	free(m_scene_manager.scenes);
}


scene_t* scene_manager_get_scene(const scene_id_t scene_id) {
	return m_scene_manager.scenes + (int) scene_id;
}


void scene_manager_change_scene(const scene_id_t scene_id) {
	m_scene_manager.should_change_scene = 1;
	m_scene_manager.next_scene_id = scene_id;
}

void scene_manager_update(const float dt) {
	scene_t* scene = scene_manager_get_scene(m_scene_manager.current_scene_id);
	scene->update(dt);
	if (m_scene_manager.should_change_scene) {
		m_scene_manager.should_change_scene = false;
		scene_manager_load_next_scene();
	}
}


void scene_manager_draw() {
	scene_t* scene = scene_manager_get_scene(m_scene_manager.current_scene_id);
	scene->draw();
}

