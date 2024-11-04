#ifndef PK_TEXTURE_POOL_H
#define PK_TEXTURE_POOL_H
#include "hash_map.h"
#include "raylib.h"
#include <stdlib.h>


typedef struct texture_pool {
    hash_map_t pool;
    size_t size;
} texture_pool_t;


void texture_pool_init();

void texture_pool_close();

Texture2D* texture_pool_at(const char* file_name);

void texture_pool_erase(const char* file_name);

void texture_pool_clear();

size_t texture_pool_size();


#endif