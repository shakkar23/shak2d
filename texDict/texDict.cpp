#include "texDict.hpp"
#include <string_view>


void SurfaceTexture::load(RenderWindow& window, std::string path, int32_t x, int32_t y, uint8_t sections){
	(*this) = TextureDictionary::getSurfaceTexture(window, path);

}


void SurfaceTexture::render(RenderWindow& window, SDL_Rect dst) {
	window.render({0,0,0,0}, dst, this->texture->texture);
}



void SpriteSheet::load(RenderWindow& window, std::string path, int32_t x, int32_t y, uint8_t sections) {

	(*this) = TextureDictionary::getSpriteSheet(window, path, x, y, sections);
}

void SpriteSheet::render(RenderWindow& window, SDL_Rect dst) {
	window.render(this->srcRect, dst, this->texture->texture);
}




Texture* TextureDictionary::loadTexture(RenderWindow& window, std::string_view p_filePath) {
	return new Texture(window, p_filePath);
}

SpriteSheet TextureDictionary::getSpriteSheet(RenderWindow& window, std::string_view path, uint32_t x, uint32_t y, uint8_t sections) {
	
	if (textures.find(path.data()) == textures.end()) {
		textures[path.data()] = loadTexture(window, path.data());
	}
	
	return SpriteSheet(x,y,sections, textures[path.data()]);
}

SurfaceTexture TextureDictionary::getSurfaceTexture(RenderWindow& window, std::string_view path) {
	if (textures.find(path.data()) == textures.end()) {
		textures[path.data()] = loadTexture(window, path);
	}
	return SurfaceTexture(window, path.data());
}