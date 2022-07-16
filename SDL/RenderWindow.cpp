//not my code
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"

#define DEFAULT_SCREEN_WIDTH 1920
#define DEFAULT_SCREEN_HEIGHT 1080

RenderWindow::RenderWindow(const char *p_title, const int p_w, const int p_h)
    : window(NULL), renderer(NULL) {
  window =
      SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (window == NULL) {
     // std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC);
  //SDL_RenderSetLogicalSize(this->renderer, logicalWindowSize, logicalWindowSize);



  SDL_Surface* surface;     // Declare an SDL_Surface to be filled in with pixel data from an image file
#define BLACK 0x0000
#define WHITE 0x0fff
  Uint16 pixels[16 * 16] = {  // ...or with raw pixel data:
    WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, BLACK, WHITE, WHITE, WHITE,
    WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE,
    WHITE, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE
  };
#undef WHITE
#undef BLACK
  surface = SDL_CreateRGBSurfaceFrom(pixels, 16, 16, 16, 16 * 2, 0x0f00, 0x00f0, 0x000f, 0xf000);

  // The icon is attached to the window pointer
  SDL_SetWindowIcon(window, surface);

  // ...and the surface containing the icon pixel data is no longer required.
  SDL_FreeSurface(surface);
}

int RenderWindow::getRefreshrate() {
  int displayIndex = SDL_GetWindowDisplayIndex(window);
  SDL_DisplayMode mode;
  SDL_GetDisplayMode(displayIndex, 0, &mode);
  return mode.refresh_rate;
}


void RenderWindow::cleanUp() { SDL_DestroyWindow(window); }

void RenderWindow::clear() { SDL_RenderClear(renderer); }

void RenderWindow::render(SDL_Rect src, SDL_Rect dst, SDL_Texture* tex) {

    auto checkIfSet = [&](SDL_Rect box) {if ((box.x == 0) && (box.y == 0) && (box.w == 0) && (box.h == 0)) return true; else return false; };

    auto err = SDL_RenderCopy(this->renderer, tex, (checkIfSet(src)) ? NULL : &src, & dst);

	if (err != 0) {
		//std::cout << "RenderCopy failed: " << SDL_GetError() << std::endl;
	}
}


void RenderWindow::display() { SDL_RenderPresent(renderer); }

void RenderWindow::getWindowSize(int& x, int& y) {
    SDL_GetWindowSize(this->window, &x, &y);
}

void RenderWindow::setWindowSize(int x, int y) {
    SDL_SetWindowSize(this->window, x, y);
}

int RenderWindow::QueryTexture(SDL_Texture* texture, Uint32* format, int* access, int* w, int* h) {
    return SDL_QueryTexture(texture, format, access, w, h);
}


SDL_Renderer* RenderWindow::getRenderer() { return renderer; }

