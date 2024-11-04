#include <raylib.h>
#include "constants.h"
#include "scene/scene.h"


int main() {
    InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
    SetTargetFPS(FPS);
    scene_manager_init();    

    while (WindowShouldClose() == false) {
        scene_manager_update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        scene_manager_draw();
        EndDrawing();
    }    
    
    CloseWindow();
    return 0;
}