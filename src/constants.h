#pragma once
#include "scene/scene_id.h"



#define RES "./resources/"


// Window
#define SCREEN_W 1280
#define SCREEN_H 720
#define SCREEN_CENTERX 640.0f
#define SCREEN_CENTERY 360.0f
#define WINDOW_TITLE "CPokeRpg"
#define FPS 60

// Game
#define MAX_ENTITIES 4096
#define MAIN_SCENE TitleScreenID

// Camera
#define CAMERA_MIN_ZINDEX 0
#define CAMERA_TERRAIN_ZINDEX 0
#define CAMERA_WATER_ZINDEX 1
#define CAMERA_SHADOW_ZINDEX 2
#define CAMERA_PLAYER_ZINDEX 3
#define CAMERA_TOP_ZINDEX 4
#define CAMERA_SKY_ZINDEX 0
#define CAMERA_MAX_ZINDEX 5
#define CAMERA_MIN_ZOOM 0.25f
#define CAMERA_MAX_ZOOM 2.25f