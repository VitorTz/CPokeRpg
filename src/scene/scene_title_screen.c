#include "scene_title_screen.h"


static image_t background[2];
static image_t logo;
static image_t press_space;


void scene_title_screen_init(scene_id_t scene_d) {
	mstring_t str;
	mstring_init(&str);
	random_file_from_dir(RES "graphics/backgrounds/", &str);
	const char* rng_file = mstring_get_str(&str);
	image_init(background, rng_file);
	image_init(background + 1, rng_file);
	background[1].pos.x = SCREEN_W;
	mstring_close(&str);	
}


void scene_title_screen_update(scene_id_t scene_d, float dt) {
	for (int i = 0; i < 2; i++) {
		image_t* img = background + i;
		img->pos.x -= dt * 150.0f;
		if (img->pos.x + img->size.x < 0.0f) {
			img->pos.x += SCREEN_W * 2.0f;
		}
	}
}


void scene_title_screen_draw(scene_id_t scene_d, float dt) {	
	Rectangle inverted_rect = { 0.0f, 0.0f, -SCREEN_W, SCREEN_H };
	image_draw(background);
	image_draw_rect(background + 1, &inverted_rect);
}