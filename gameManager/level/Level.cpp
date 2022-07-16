#include "Level.hpp"

constexpr void levels::set(int x, int y, levelData data)noexcept {
if(x < 0 || x >= getWidth() || y < 0 || y >= getHeight()) return;
	level[x][y] = data;
}
constexpr levelData levels::get(int x, int y)const noexcept {
	return level.at(x).at(y);
}
constexpr int levels::getWidth()const noexcept {
return level.size();
}
constexpr int levels::getHeight() const noexcept{
return level.at(0).size();
}