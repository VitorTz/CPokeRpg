#include <raylib.h>
#include "scene/scene.h"
#include "constants.h"
#include "util/texture_pool.h"
#include "ecs/ecs_manager.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(FPS);

	texture_pool_init();
	ecs_manager_init();
	scene_manager_init();

	while (!WindowShouldClose()) {
		scene_manager_update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);		
		scene_manager_draw();
		EndDrawing();
	}

	ecs_manager_close();
	scene_manager_close();	
	texture_pool_close();
	CloseWindow();
	return 0;
}