#include "scene_world.h"


void scene_world_init() {
	ecs_manager_create_ecs(WorldSceneID);
}


void scene_world_update(const float dt) {
	ecs_manager_set_current_instance(WorldSceneID);
	ecs_instance_t* ecs = ecs_manager_get_ecs();
	ecs_instance_update(ecs, dt);
}


void scene_world_draw() {
	ecs_manager_set_current_instance(WorldSceneID);
	ecs_instance_t* ecs = ecs_manager_get_ecs();
	ecs_instance_draw(ecs);
}