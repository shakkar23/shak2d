#pragma once

#include <map>
#include <string>
#include <string_view>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../SDL/RenderWindow.hpp"
#include "../game/inGame/Entities/Renderable.hpp"

class RenderWindow;

class Texture {
public:
	Texture() = default;
	Texture(RenderWindow& window, std::string_view path) {
		auto surface = IMG_Load(path.data());

		width = surface->w;
		height = surface->h;

		SDL_Texture* texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
		SDL_FreeSurface(surface);

		this->texture = texture;
	}
	void load(RenderWindow& window, std::string_view path) {
		auto surface = IMG_Load(path.data());

		width = surface->w;
		height = surface->h;

		SDL_Texture* texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
		SDL_FreeSurface(surface);

		this->texture = texture;
	}
	~Texture() {
		if (texture)
			SDL_DestroyTexture(texture);
	}
	SDL_Texture* texture;
	uint8_t width;
	uint8_t height;
};

class SurfaceTexture : public Renderable {
public:
	SurfaceTexture() {}
	SurfaceTexture(RenderWindow &window, std::string_view path){
		surface = IMG_Load(path.data());
		
	}
	void load(RenderWindow& window, std::string path, int32_t x, int32_t y, uint8_t sections) override;
	void render(RenderWindow& renderer, SDL_Rect dst) override;
	
	~SurfaceTexture() {
		if (surface)
			SDL_FreeSurface(surface);
	}
	SDL_Surface* surface;
	Texture* texture;
};

class SpriteSheet : public Renderable {
	public:
	SpriteSheet()= default;
	SpriteSheet(int32_t x, int32_t y, uint8_t sections, Texture *tex) {
		
		// set class members
		this->texture = tex;
		this->sections = sections;
		this->srcRect = {sections * x, sections * y, sections, sections };
		this->destRect = {0, 0, sections, sections };
	}
	// the x and y are 0,0 on the top left of the texture
	void load(RenderWindow& window, std::string path, int32_t x, int32_t y, uint8_t sections) override;
	void render(RenderWindow& renderer, SDL_Rect dst) override;
	~SpriteSheet() {
		
	}
	SDL_Rect srcRect = {0,0,0,0};
	SDL_Rect destRect = {0,0,0,0};
	Texture* texture = nullptr;
	uint8_t sections = 0;
};

class TextureDictionary {
public:
	static SurfaceTexture getSurfaceTexture(RenderWindow& window, std::string_view path);
	static SpriteSheet getSpriteSheet(RenderWindow& window, std::string_view path, uint32_t x, uint32_t y, uint8_t sections);


private:
	static Texture* loadTexture(RenderWindow& window, std::string_view p_filePath);
	static inline std::map<std::string, Texture*> textures;
};