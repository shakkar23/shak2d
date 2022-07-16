#pragma once
#include <array>

enum class levelData
{
	sky,
	dirt,
	stone
};
class levels { 
	public:
		levels() = default;
		~levels() = default;
		constexpr void set(int x, int y, levelData data)noexcept;
		constexpr levelData get(int x, int y)const noexcept;
		constexpr int getWidth()const noexcept;
		constexpr int getHeight()const noexcept;
	std::array<std::array<levelData,200 >, 2000> level;
};