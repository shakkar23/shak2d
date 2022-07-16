#pragma once
//not my code
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "autoTex.hpp"
#include "../gameManager/gameManager.hpp"
constexpr inline auto UPDATES_A_SECOND = 100;
constexpr inline auto DELTATIME = (1.0f / (float)UPDATES_A_SECOND);

void pressKey(SDL_Scancode scan, const moveDirection& player);
void unpressKey(SDL_Scancode scan, const moveDirection &player);