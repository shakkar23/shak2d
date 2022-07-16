#pragma once
#include "../../moveDirection.hpp"

struct boundingBox{
	public:
		float x, y, w, h;
};

struct velocity{
public:
	float x, y;
};
struct acceleration{
	public:
	float x, y;
};

class Updatable {

	public:
		Updatable() : boundingBox({0,0,0,0}), velocity({0,0}), acceleration({0,0}), isOnGround(false) {}
	virtual void update(const moveDirection& prevplayer, const moveDirection& player, float deltaTime) = 0;
	boundingBox boundingBox;
	velocity velocity;
	acceleration acceleration;
	bool isOnGround;
};