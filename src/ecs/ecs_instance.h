#pragma once
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"
#include "../util/camera.h"


typedef struct ecs_instance {
	entity_manager_t entity;
	component_manager_t component;
	system_manager_t system;
	camera_t* camera;
	vector_t entities_to_destroy;
	vector_t static_collisions;
	int should_destroy_all_entities;
} ecs_instance_t;


void ecs_instance_init(ecs_instance_t* ecs);

void ecs_instance_close(ecs_instance_t* ecs);

void ecs_instance_add_component(
	ecs_instance_t* ecs,
	entity_t e,
	component_t id,
	const void* component
);


void* ecs_instance_get_component(
	ecs_instance_t* ecs,
	entity_t e,
	component_t id
);


transform_t* ecs_instance_get_transform(
	ecs_instance_t* ecs,
	entity_t e
);

void ecs_instance_rmv_component(
	ecs_instance_t* ecs,
	entity_t e,
	component_t id
);


void ecs_instance_destroy_entity(ecs_instance_t* ecs, entity_t e);

void ecs_instance_destroy_entity_immediate(ecs_instance_t* ecs, entity_t e);

void ecs_instance_destroy_all_entities(ecs_instance_t* ecs);

void ecs_instance_destroy_all_entities_immediate(ecs_instance_t* ecs);

void ecs_instance_update(ecs_instance_t* ecs, float dt);

void ecs_instance_draw(ecs_instance_t* ecs);