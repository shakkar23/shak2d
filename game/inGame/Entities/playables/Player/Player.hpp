#pragma once
#include <stdint.h>
#include <string>

#include <SDL2/SDL.h>
#include "../../../Updatable.hpp"
#include "../../Renderable.hpp"
#include "../../../../../texDict/texDict.hpp"


class Player : public SpriteSheet , public Updatable
{
	public:
		Player() : name("GUH"), health(100) {}

	void update(const moveDirection& prevplayer, const moveDirection& player, float deltaTime) override;
	
	

	void setName(std::string name);
	std::string getName();
	
	void setHealth(int16_t health);
	int16_t getHealth();
	
public:
	
	std::string name;
	int16_t health;
	
};
