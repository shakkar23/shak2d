#pragma once

#include "../moveDirection.hpp"
#include "../SDL/RenderWindow.hpp"
#include "../SDL/autoTex.hpp"
#include "../texDict/texDict.hpp"
#include "../game/inGame/Entities/Renderable.hpp"
#include "../game/inGame/Updatable.hpp"
#include "level/Level.hpp"
#include <thread>
#include <array>

// this is the gameManager, it redirects the thread to wherever it needs to go
constexpr auto VisibleTilesX = 10;
class gameManager
{
public:
	void Init(RenderWindow& window);
	void gameLogic(const moveDirection& prevplayer, const moveDirection& player);
	void render(RenderWindow &window);

private:
	void collision();
	bool winCondition();
	void movement(const moveDirection& prevplayer, const moveDirection& player);
	levelData GetTile(float x, float y);
	std::vector<SpriteSheet*> tex0{};
	std::vector<SurfaceTexture*> tex1{};
	SpriteSheet dirt;
	SpriteSheet stone;
	SpriteSheet sky;
	SpriteSheet player;
	SurfaceTexture background;
	std::vector<Renderable*> renderableObjects;
	std::vector<Updatable*> updateableObjects;
	bool won = false;
	levels level0;
	float cameraX = 0;
	float cameraY = 0;
	float fPlayerPosX = 2;
	float fPlayerPosY = 12;
	float fPlayerVelX = 0;
	float fPlayerVelY = 0;
	float fPlayerAccX = 0;
	float fPlayerAccY = 0;
	bool bPlayerOnGround = false;
};
extern gameManager GameManager;
