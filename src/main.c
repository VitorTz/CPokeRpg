#include <raylib.h>
#include "constants.h"
#include "scene/scene.h"
#include "util/texture_pool.h"


int main() {
    InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
    SetTargetFPS(FPS);
    scene_manager_init();

    texture_pool_init();
        

    while (WindowShouldClose() == false) {
        scene_manager_update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        scene_manager_draw();
        Texture2D* t1 = texture_pool_at(RES "graphics/characters/player.png");
        Texture2D* t2 = texture_pool_at(RES "graphics/characters/straw.png");
        DrawTexture(*t1, 0, 0, WHITE);
        DrawTexture(*t2, 300, 300, WHITE);
        EndDrawing();
    }    

    texture_pool_close();
    CloseWindow();
    return 0;
}