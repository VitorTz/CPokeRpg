#include "texture_pool.h"



static hash_map_t* map;

static int t_is_equal(void* l, void* r) {
	return ((Texture2D*)l)->id == ((Texture2D*)r)->id;
}


void texture_pool_init() {
	map = hash_map_create(sizeof(Texture2D), 256, hash_str);
}


void texture_pool_close() {
	texture_pool_clear();
	hash_map_destroy(map);
}


Texture2D* texture_pool_get(const char* file_name) {
	const hash_map_query_t q = hash_map_try_insert(map, file_name);
	// Se não obteve sucesso ao inserir então já existe
	if (!q.success) {
		return (Texture2D*) q.data;
	}	
	Texture2D* t = (Texture2D*) q.data;
	*t = LoadTexture(file_name);
	assert(t->id > 0);
	printf("[TEXTURE %d LOADED!]\n", t->id);
	return t;
}


void texture_pool_clear() {
	const iterator_t m_iter = hash_map_iterator(map);
	for (vector_t* v = m_iter.begin; v < m_iter.end; v++) {
		iterator_t v_iter = vector_iterator(v);
		for (char* p = v_iter.begin; p < v_iter.end; p += v->t_size) {
			Texture2D* t = (Texture2D*) (p + sizeof(size_t));
			UnloadTexture(*t);
		}
		vector_clear(v);
	}
}


void texture_pool_erase(const char* file_name) {
	const hash_map_query_t q = hash_map_contains(map, file_name);
	if (q.success) {
		UnloadTexture(*((Texture2D*) q.data));
		hash_map_erase(map, file_name);
	}
}


size_t texture_pool_size() {
	return map->size;
}