#include "texture_pool.h"
#include "util.h"


static hash_map_t texture_pool;


void texture_pool_init() {
	hash_map_init(&texture_pool, sizeof(Texture2D), 64, hash_str);	
}


void texture_pool_close() {
	const vec_iterator_t iter = hash_map_get_vec_iterator(&texture_pool);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		const iterator_t viter = vector_iterator(v);
		for (char* p = viter.begin; p < viter.end; p += viter.step) {
			const Texture2D* texture = (Texture2D*)(p + sizeof(size_t));
			UnloadTexture(*texture);
		}
		vector_close(v);
	}
	free(texture_pool.buckets);
}


Texture2D* texture_pool_get(const char* file_name) {
	hash_map_query_t q = hash_map_allocate(&texture_pool, file_name);
	Texture2D* texture = (Texture2D*) q.value;
	if (q.success) {
		*texture = LoadTexture(file_name);		
	}
	return texture;
}


size_t texture_pool_size() {
	return texture_pool.size;
}