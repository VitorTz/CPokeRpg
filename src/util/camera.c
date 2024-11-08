#include "camera.h"
#include "../ecs/ecs_manager.h"


static vector_t vector_aux;
static vector_t entities_to_draw;

void camera_init_aux_vec() {
	vector_init(&vector_aux, sizeof(entity_pair_t));
	vector_reserve(&vector_aux, MAX_ENTITIES);
	vector_init(&entities_to_draw, sizeof(entity_t));
	vector_reserve(&entities_to_draw, MAX_ENTITIES);
	vector_aux.size = MAX_ENTITIES;
}


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
		entity_pair_t pair = { 0.0f, e };
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


void camera_begin_drawing(camera_t* camera) {
	BeginMode2D(camera->camera2D);
}


void camera_end_drawing() {
	EndMode2D();
}

void camera_sort_entities_aux(vector_t* entities, const size_t exp) {		
	const size_t n = entities->size;
	size_t count[10] = { 0 };

	// Contagem das ocorrências dos dígitos
	iterator_t iter = vector_iterator(entities);
	entity_pair_t* begin = (entity_pair_t*) iter.begin;
	entity_pair_t* end = (entity_pair_t*) iter.end;

	for (entity_pair_t* pair = begin; pair < end; pair++) {
		count[(pair->e / exp) % 10]++;

	}	

	// Atualizando count[i] para que ele contenha a posição final de cada dígito
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}

	// Construindo o array de saída	
	for (entity_pair_t* pair = end - 1; pair >= begin; pair--) {
		vector_set(
			&vector_aux,
			count[(pair->e / exp) % 10] - 1,
			pair
		);
	}
	

	// Copiando o array de saída para arr[], para que arr[] agora contenha os números ordenados
	iter = vector_iterator(&vector_aux);
	size_t i = 0;
	for (entity_pair_t* pair = iter.begin; pair < iter.end; pair++) {
		vector_set(entities, i++, pair);
	}	
}

void camera_sort_entities(vector_t* entities) {	
	for (int exp = 1; MAX_ENTITIES / exp > 0; exp *= 10) {
		camera_sort_entities_aux(entities, exp);
	}
}


void camera_draw(camera_t* c, system_manager_t* system_manager) {
	ecs_instance_t* ecs = ecs_manager_get_ecs();
	camera_begin_drawing(c);
	for (zindex_t z = CAMERA_MIN_ZINDEX; z <= CAMERA_MAX_ZINDEX; z++) {
		vector_t* v = (vector_t*) hash_map_at(&c->zindex_to_entities, &z);
		const iterator_t iter = vector_iterator(v);
		for (entity_pair_t* pair = iter.begin; pair < iter.end; pair++) {
			transform_t* t = ecs_instance_get_transform(ecs, pair->e);
			pair->y_pos = t->pos.y + t->size.y / 2.0f;
		}
		camera_sort_entities(v);
		system_manager_draw(system_manager, v);
	}
	camera_end_drawing();
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