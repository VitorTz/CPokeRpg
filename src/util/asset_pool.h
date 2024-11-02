#pragma once
#include <raylib.h>
#include <unordered_map>
#include "fontid.h"


namespace pk {

	typedef struct asset_pool {
		std::unordered_map<std::size_t, Texture2D> texturePool{};
		std::unordered_map<pk::FontID, Font> fontPool{};
	} asset_pool_t;

	void asset_pool_init();
	void asset_pool_close();

	Texture2D asset_pool_get_texture(const char* fileName);
	Texture2D* asset_pool_get_texture_ptr(const char* fileName);
	void asset_pool_erase_texture(const char* fileName);
	
	const Font& asset_pool_get_font(pk::FontID fontId);

	std::size_t asset_pool_num_textures();

}