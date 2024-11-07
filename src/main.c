#include <raylib.h>
#include "scene/scene.h"
#include "constants.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(FPS);

	scene_manager_init();	

	while (!WindowShouldClose()) {
		scene_manager_update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
		scene_manager_draw();
		EndDrawing();
	}

	scene_manager_close();	
	CloseWindow();
	return 0;
}