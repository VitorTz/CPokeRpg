#include <assert.h>
#include <raylib.h>
#include "iterator.h"
#include "util.h"
#include "texture_pool.h"
#include "hash_map.h"
#include "vector.h"


static texture_pool_t m_texture_pool;


void texture_pool_init() {
    hash_map_init(&m_texture_pool.pool, 256, sizeof(Texture2D));
    m_texture_pool.size = 0;
}


void texture_pool_close() {
    texture_pool_clear();
    hash_map_close(&m_texture_pool.pool);
}


void texture_pool_clear() {
    hash_map_iterator_t map_iter = hash_map_get_iterator(&m_texture_pool.pool);
    for (vector_t* v = map_iter.begin; v != map_iter.end; v += map_iter.step) {
        iterator_t vec_iter = vector_get_iterator(v);
        for (char* p = vec_iter.begin; p != vec_iter.end; p += vec_iter.step) {
            Texture2D* texture = (Texture2D*) (p + sizeof(size_t));
            UnloadTexture(*texture);
        }
    }
}


Texture2D* texture_pool_at(const char* file_name) {
    const size_t h = hash(file_name);
    const hash_map_query_t query = hash_map_contains(&m_texture_pool.pool, h);
    Texture2D* texture = (Texture2D*) query.data;
    if (!query.success) {
        *texture = LoadTexture(file_name);
        m_texture_pool.size++;
        assert(texture->id > 0);
    }
    return texture;
}


void texture_pool_erase(const char *file_name) {
    const size_t h = hash(file_name);    
    const hash_map_query_t query = hash_map_contains(&m_texture_pool.pool, h);
    if (query.success) {
        UnloadTexture(*((Texture2D*) query.data));
        hash_map_erase(&m_texture_pool.pool, h);
        m_texture_pool.size--;
    }
}


size_t texture_pool_size() {
    return m_texture_pool.size;
}