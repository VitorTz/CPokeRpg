#include "scene.h"
#include "../util/image.h"
#include <raylib.h>
#include <array>


static std::array<pk::image_t, 2> mbackground{};
static const Rectangle mrect_inverted_image{
	0.0f,
	0.0f,
	-pk::SCREEN_W,
	pk::SCREEN_H
};


void pk::scene_title_screen_init() {
	mbackground[0] = pk::image_t{ RES "graphics/backgrounds/forest.png" };
	mbackground[1] = pk::image_t{ RES "graphics/backgrounds/forest.png" };
	mbackground[1].pos = Vector2{ pk::SCREEN_W, 0.0f };
}


void pk::scene_title_screen_update(const float dt) {	
	for (pk::image_t& img : mbackground) {
		img.pos.x -= dt * 150.0f;
		if (img.pos.x + pk::SCREEN_W < 0.0f) {
			img.pos.x += pk::SCREEN_W * 2.0f;
		}
	}
	if (IsKeyPressed(KEY_SPACE)) {
		pk::scene_manager_change_scene(pk::WorldSceneID);
	}
}


void pk::scene_title_screen_draw() {
	pk::image_draw(mbackground[0]);	
	pk::image_draw_rect(mbackground[1], mrect_inverted_image);
}