#include "ecs_instance.h"


void ecs_instance_init(ecs_instance_t* ecs) {
	entity_manager_init(&ecs->entity);
	component_manager_init(&ecs->component);
	system_manager_init(&ecs->system);
	ecs->camera = (camera_t*)malloc(sizeof(camera_t));
	camera_init(ecs->camera);
	vector_init(&ecs->entities_to_destroy, sizeof(entity_t));
	vector_reserve(&ecs->entities_to_destroy, 256);
	vector_init(&ecs->static_collisions, sizeof(Rectangle));
	vector_reserve(&ecs->static_collisions, 1024);
	ecs->should_destroy_all_entities = 0;
}


void ecs_instance_close(ecs_instance_t* ecs) {
	entity_manager_close(&ecs->entity);
	component_manager_close(&ecs->component);
	system_manager_close(&ecs->system);
	camera_close(ecs->camera);
	vector_close(&ecs->static_collisions);
	vector_close(&ecs->entities_to_destroy);
	free(ecs->camera);
}


void ecs_instance_add_component(
	ecs_instance_t* ecs,
	const entity_t e,
	const component_t id,
	const void* component
) {
	component_manager_add(
		&ecs->component,
		e,
		id,
		component
	);
	system_manager_add(
		&ecs->system,
		e,
		id
	);
}


void* ecs_instance_get_component(
	ecs_instance_t* ecs,
	const entity_t e,
	const component_t id
) {
	return component_manager_get(&ecs->component, e, id);
}


transform_t* ecs_instance_get_transform(ecs_instance_t* ecs, const entity_t e) {
	return (transform_t*)ecs_instance_get_component(ecs, e, TRANSFORM_ID);
}


void ecs_instance_rmv_component(
	ecs_instance_t* ecs,
	const entity_t e,
	const component_t id
) {
	component_manager_erase(&ecs->component, e, id);
	system_manager_erase(&ecs->system, e, id);
}


void ecs_instance_destroy_entity(ecs_instance_t* ecs, entity_t e) {
	vector_push_back(&ecs->entities_to_destroy, &e);
}

void ecs_instance_destroy_entity_immediate(ecs_instance_t* ecs, entity_t e) {
	const zindex_t z = ecs_instance_get_transform(ecs, e)->zindex;
	camera_erase(ecs->camera, e, z);
	entity_manager_entity_destroy(&ecs->entity, e);
	component_manager_entity_destroy(&ecs->component, e);
	system_manager_entity_destroy(&ecs->system, e);
}

void ecs_instance_destroy_all_entities(ecs_instance_t* ecs) {
	ecs->should_destroy_all_entities = 1;
}

void ecs_instance_destroy_all_entities_immediate(ecs_instance_t* ecs) {
	camera_clear(ecs->camera);
	entity_manager_clear(&ecs->entity);
	component_manager_clear(&ecs->component);
	system_manager_clear(&ecs->system);	
}


void ecs_instance_update(ecs_instance_t* ecs, const float dt) {
	system_manager_update(&ecs->system, dt);

	if (ecs->should_destroy_all_entities) {
		ecs_instance_destroy_all_entities_immediate(ecs);
		ecs->should_destroy_all_entities = 0;
	}

	while (!vector_is_empty(&ecs->entities_to_destroy)) {
		entity_t e;
		vector_pop_back(&ecs->entities_to_destroy, &e);
		ecs_instance_destroy_entity_immediate(ecs, e);
	}
}


void ecs_instance_draw(ecs_instance_t* ecs) {
	camera_draw(ecs->camera, &ecs->system);
}