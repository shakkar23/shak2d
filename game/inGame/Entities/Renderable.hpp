#pragma once
#include <string>
#include <concepts>

#include "SDL2/SDL.h"

#include "../../../SDL/RenderWindow.hpp"

/*
template <typename T>
concept CanRender = requires(T t, RenderWindow window, std::string path, int32_t x, int32_t y, uint8_t sections) {
	{ t.load(window, path, x, y, sections) } -> std::same_as<void>;
};

template<CanRender T>
class Renderable :public T{

public:
	Renderable() = default;
	Renderable(RenderWindow& window, std::string path, int32_t x, int32_t y, uint8_t sections);
	void  load(RenderWindow& window, std::string path, int32_t x, int32_t y, uint8_t sections);
	void render(RenderWindow& renderer, SDL_Rect dst);
	T instance;
};*/




class Renderable {
public:
	virtual void load(RenderWindow& window, std::string path, int32_t x, int32_t y, uint8_t sections) = 0;
	virtual void render(RenderWindow& renderer, SDL_Rect dst) = 0;
};