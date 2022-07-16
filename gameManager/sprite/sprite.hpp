#include "../../helper/Coord.hpp"
#include <stdint.h>


/// <summary>
/// sprites are rendered things on screen that can be moved around and have some sort of collision based on its spriteType
/// </summary>
class sprite {
	constexpr inline sprite(Coord pos, Coord size) : pos(pos), size(size) noexcept {}
	constexpr inline sprite(int x, int y, int w, int h) : pos(x, y), size(w, h)noexcept {}
	Coord<int16_t> pos;
	Coord<int16_t> size;
	enum spriteType : int8_t
	{
		Player,
		Enemy,
		Bullet,
		PowerUp,
		NPC
	} kind;
	
};