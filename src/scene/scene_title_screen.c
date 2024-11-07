#include "scene_title_screen.h"


static image_t background[2];
static image_t logo;
static image_t press_space;
static const Rectangle inverted_rect = { 0.0f, 0.0f, -SCREEN_W, SCREEN_H };


void scene_title_screen_init() {
	string_t str;
	string_init(&str);
	random_file_from_dir(RES "graphics/backgrounds/", &str);
	const char* rng_file = string_get(&str);

	image_init(background, rng_file);
	image_init(background + 1, rng_file);
	background[1].pos.x = SCREEN_W;

	string_close(&str);
}


void scene_title_screen_update(float dt) {
	for (int i = 0; i < 2; i++) {
		image_t* img = background + i;
		img->pos.x -= dt * 150.0f;
		if (img->pos.x + img->size.x < 0.0f) {
			img->pos.x += SCREEN_W * 2.0f;
		}
	}
	if (IsKeyPressed(KEY_SPACE)) {
		scene_manager_change_scene(WorldSceneID);
	}
}


void scene_title_screen_draw() {	
	image_draw(background);
	image_draw_rect(background + 1, &inverted_rect);
}