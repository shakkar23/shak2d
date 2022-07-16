//not my code#
#pragma once
#ifndef SHAK_RENDER_WINDOW
#define SHAK_RENDER_WINDOW

// this is for both x and y of the screen because square
//constexpr inline auto logicalWindowSize = 1000;
constexpr inline auto logicalWindowBottom = 0;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

//cpp bullshit


class RenderWindow {
public:
  RenderWindow(const char *p_title, int p_w, int p_h);
  

  int getRefreshrate();
  void cleanUp();
  void clear();
  void render(SDL_Rect src, SDL_Rect dst, SDL_Texture* tex);
  void display(); 
  void getWindowSize(int& x, int&y);
  SDL_Renderer* getRenderer();
  void setWindowSize(int x, int y);
  int QueryTexture(SDL_Texture* texture, Uint32* format, int* access, int* w, int* h);
private:
  SDL_Window *window;
  SDL_Renderer *renderer;

};

#endif