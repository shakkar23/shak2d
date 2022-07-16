
#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include<utility>

#include "RenderWindow.hpp"
#include "../texDict/texDict.hpp"

class RenderWindow; //cpp bullshit


//make sure to set the sprite at the very least! otherwise your png will not be shown
class autoTexture {
public:
	 autoTexture() {};
	~autoTexture() {};

	// the canvas of the window is by default a grid of 1920 by 1080 for standardization in position purposes, please use it 
	// data structure: x cord, y cord, x size, y size
	SDL_Rect sprite{};
	// x cord, y cord, x size, y size that you choose
	SDL_Rect textureRegion{};
	SDL_Texture *tex = nullptr;
	SDL_Rect getSprite();
	SDL_Texture* getTex();
	SDL_Rect getTextureRegion();

	autoTexture(const autoTexture& other) = delete;				// Copy constructor
	autoTexture& operator=(const autoTexture& other) noexcept = default;	// Copy assignment operator
	autoTexture(autoTexture&& other) noexcept :sprite(other.sprite) { other.sprite = { 0,0,0,0 }; } // move constructor
	autoTexture& operator=(autoTexture&& other) noexcept = default;	// move assignment operator

private:
};