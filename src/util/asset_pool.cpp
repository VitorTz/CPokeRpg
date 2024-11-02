#include <cassert>
#include "asset_pool.h"
#include "util.h"
#include "../constants.h"


static pk::asset_pool_t masset_pool{};


void pk::asset_pool_init() {
	masset_pool.texturePool.reserve(256);
	masset_pool.fontPool.emplace(pk::Light, LoadFont(FONT_PATH "Light.ttf"));
	masset_pool.fontPool.emplace(pk::Regular, LoadFont(FONT_PATH "Regular.ttf"));
	masset_pool.fontPool.emplace(pk::SemiBold, LoadFont(FONT_PATH "SemiBold.ttf"));
	masset_pool.fontPool.emplace(pk::Bold, LoadFont(FONT_PATH "Bold.ttf"));
}


void pk::asset_pool_close() {
	for (auto& pair : masset_pool.texturePool) {
		UnloadTexture(pair.second);
	}
	for (auto& pair : masset_pool.fontPool) {
		UnloadFont(pair.second);
	}
	masset_pool.texturePool.clear();
	masset_pool.fontPool.clear();
}


Texture2D pk::asset_pool_get_texture(const char* fileName) {
	const std::size_t h = pk::hash(fileName);
	if (masset_pool.texturePool.find(h) == masset_pool.texturePool.end()) {
		const Texture2D t = LoadTexture(fileName);
		assert(t.id > 0);
		masset_pool.texturePool.emplace(h, t);
	}
	return masset_pool.texturePool[h];
}


Texture2D* pk::asset_pool_get_texture_ptr(const char* fileName) {
	const std::size_t h = pk::hash(fileName);
	if (masset_pool.texturePool.find(h) == masset_pool.texturePool.end()) {
		const Texture2D t = LoadTexture(fileName);
		assert(t.id > 0);
		masset_pool.texturePool.emplace(h, t);
	}
	return &masset_pool.texturePool[h];
}


void pk::asset_pool_erase_texture(const char* fileName) {
	const std::size_t h = pk::hash(fileName);
	if (masset_pool.texturePool.find(h) != masset_pool.texturePool.end()) {
		UnloadTexture(masset_pool.texturePool[h]);
	}
	masset_pool.texturePool.erase(h);
}


const Font& pk::asset_pool_get_font(const pk::FontID fontId) {
	return masset_pool.fontPool[fontId];
}


std::size_t pk::asset_pool_num_textures() {
	return masset_pool.texturePool.size();
}