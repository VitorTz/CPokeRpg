#pragma once
#include <raylib.h>
#include "asset_pool.h"


namespace pk {


	typedef struct image {
		Texture2D* texture{ nullptr };
		Vector2 pos{};
		Vector2 size{};
		image() = default;
		explicit image(
			const char* fileName
	) : texture(pk::asset_pool_get_texture_ptr(fileName)),
		size(Vector2{static_cast<float>(texture->width), static_cast<float>(texture->height)}) {  }
	} image_t;

	void image_set_center(pk::image_t& image, Vector2 center);	
	void image_draw(const pk::image_t& image);
	void image_draw_rect(const pk::image_t& img, const Rectangle& rect);

}