#include <raylib.h>
#include "scene/scene.h"
#include "constants.h"
#include "util/asset_pool.h"


int main() {
	InitWindow(pk::SCREEN_W, pk::SCREEN_H, pk::WINDOW_TITLE);
	SetTargetFPS(pk::FPS);
	
	pk::asset_pool_init();
	pk::scene_manager_init();

	while (WindowShouldClose() == false) {
		pk::scene_manager_update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
		pk::scene_manager_draw();
		EndDrawing();
	}

	pk::asset_pool_close();
	CloseWindow();
	return 0;
}