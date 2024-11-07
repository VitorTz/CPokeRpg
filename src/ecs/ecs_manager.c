#include "ecs_manager.h"

static ecs_manager_t mecs_manager;


void ecs_manager_init() {
	hash_map_init(&mecs_manager.ecs_map, sizeof(ecs_instance_t), (size_t) NumScenes, hash_scene_id);	
}


void ecs_manager_close() {	
	const vec_iterator_t iter = hash_map_get_vec_iterator(&mecs_manager.ecs_map);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		const iterator_t viter = vector_iterator(v);
		for (char* p = viter.begin; p < viter.end; p += viter.step) {
			ecs_instance_t* ecs = (ecs_instance_t*) (p + sizeof(size_t));
			ecs_instance_close(ecs);
		}				
	}
	free(mecs_manager.ecs_map.buckets);	
}


void ecs_manager_create_ecs(const scene_id_t scene_id) {
	hash_map_query_t q = hash_map_allocate(&mecs_manager.ecs_map, &scene_id);
	if (q.success) {
		ecs_instance_t* ecs = (ecs_instance_t*)q.value;
		ecs_instance_init(ecs);		
	}
}


void ecs_manager_destroy_ecs(const scene_id_t scene_id) {	
	hash_map_query_t q = hash_map_find(&mecs_manager.ecs_map, &scene_id);	
	if (q.success) {
		ecs_instance_t* ecs = (ecs_instance_t*) q.value;
		ecs_instance_close(ecs);
		hash_map_erase(&mecs_manager.ecs_map, &scene_id);
	}
}

void ecs_manager_set_current_instance(const scene_id_t scene_id) {
	mecs_manager.ecs = (ecs_instance_t*) hash_map_at(&mecs_manager.ecs_map, &scene_id);
}

ecs_instance_t* ecs_manager_get_ecs() {
	return mecs_manager.ecs;
}