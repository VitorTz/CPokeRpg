#pragma once
#include "util/sceneid.h"

#define RES "./resources/"
#define FONT_PATH RES "data/font/Poppins/"


namespace pk {

	constexpr float SCREEN_W{ 1280.0f };
	constexpr float SCREEN_H{ 720.0f };
	constexpr char WINDOW_TITLE[]{ "PokemonCPP" };
	constexpr int FPS{ 60 };

	constexpr pk::SceneID MAIN_SCENE{ pk::TitleScreenID };

}