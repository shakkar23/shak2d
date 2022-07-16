//not my code
#include "autoTex.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Rect autoTexture::getSprite() { return sprite; }

SDL_Rect autoTexture::getTextureRegion() { return textureRegion; }

SDL_Texture* autoTexture::getTex() { return tex; }
