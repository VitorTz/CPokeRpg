#pragma once
#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include "hash_map.h"
#include "util.h"


void texture_pool_init();

void texture_pool_close();

Texture2D* texture_pool_get(const char* file_name);

void texture_pool_clear();

void texture_pool_erase(const char* file_name);

size_t texture_pool_size();