#include "camera.h"


void camera_init(camera_t* c) {
	hash_map_init(&c->zindex_to_entities, sizeof(entity_t), CAMERA_MAX_ZINDEX, hash_zindex);	
	for (zindex_t z = CAMERA_MIN_ZINDEX; z <= CAMERA_MAX_ZINDEX; z++) {
		hash_map_query_t q = hash_map_allocate(&c->zindex_to_entities, &z);
		vector_t* vec = (vector_t*)q.value;
		vector_init(vec, sizeof(entity_pair_t));
		vector_reserve(vec, MAX_ENTITIES / 2);
	}
	c->camera2D.offset.x = SCREEN_CENTERX;
	c->camera2D.offset.y = SCREEN_CENTERY;
	c->camera2D.target.x = SCREEN_CENTERX;
	c->camera2D.target.y = SCREEN_CENTERY;
	c->camera2D.rotation = 0.0f;
	c->camera2D.zoom = 1.0f;
	c->size = 0;
	for (int i = 0; i < MAX_ENTITIES; i++) {
		c->is_on_camera[i] = '0';
	}
}


void camera_close(camera_t* c) {
	hash_map_close(&c->zindex_to_entities);
}


void camera_insert(camera_t* c, const entity_t e, const zindex_t zindex) {
	if (c->is_on_camera[e] == '0') {
		c->is_on_camera[e] = '1';
		vector_t* vec = (vector_t*) hash_map_at(&c->zindex_to_entities, &zindex);
		entity_pair_t pair = { e, 0.0f };
		vector_push_back(vec, &pair);		
		c->size++;
	}
}


void camera_erase(camera_t* c, const entity_t e, const zindex_t zindex) {
	if (c->is_on_camera[e] == '1') {
		c->is_on_camera[e] = '0';
		vector_t* vec = (vector_t*) hash_map_at(&c->zindex_to_entities, &zindex);
		const iterator_t iter = vector_iterator(vec);
		size_t i = 0;
		for (entity_pair_t* pair = iter.begin; pair < iter.end; pair++) {
			if (pair->e == e) {
				vector_erase(vec, i);
				c->size--;
				return;
			}
			i++;
		}		
	}
}


void camera_add_zoom(camera_t* c, const float zoom) {
	c->camera2D.zoom = fclamp(c->camera2D.zoom + zoom, CAMERA_MIN_ZOOM, CAMERA_MAX_ZOOM);
}


void camera_set_zoom(camera_t* c, const float zoom) {
	c->camera2D.zoom = fclamp(zoom, CAMERA_MIN_ZOOM, CAMERA_MAX_ZOOM);
}


void camera_set_target(camera_t* c, const Vector2 target) {
	c->camera2D.target = target;
}


void camera_draw(camera_t* c, system_manager_t* system_manager) {

}


void camera_clear(camera_t* c) {
	const vec_iterator_t iter = hash_map_get_vec_iterator(&c->zindex_to_entities);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_clear(v);
	}	
	for (int i = 0; i < MAX_ENTITIES; i++) {
		c->is_on_camera[i] = '0';
	}
	c->size = 0;
}


size_t camera_num_entities(camera_t* c) {
	return c->size;
}