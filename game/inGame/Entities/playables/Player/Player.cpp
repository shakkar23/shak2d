#include "Player.hpp"
#include <algorithm>


void Player::update(const moveDirection& prevplayer, const moveDirection& player, float deltaTime) {


    if (player.Down) {
        velocity.y += 6.0f * deltaTime;
    }
    if (player.Jump && prevplayer.Jump) {
        if (isOnGround)
            velocity.y -= 6.0f;
		
        velocity.y -= 1.0f;
    }
    if (player.Left) {
        velocity.x += (isOnGround ? -25.0f : -15.0f) * deltaTime;
    }
    if (player.Right) {
        velocity.x += (isOnGround ? 25.0f : 15.0f) * deltaTime;
    }
    // Clamp velocities between -100 and 100
    velocity.x = std::clamp(velocity.x, -100.0f, 100.0f);
    velocity.y = std::clamp(velocity.y, -100.0f, 100.0f);

	//gravity
    const  auto grav = 20.0f * deltaTime;
    velocity.y += grav;

    if (isOnGround)
    {
        velocity.x += -3.0f * velocity.y * deltaTime;
        if (fabs(velocity.x) < 0.05f)
            velocity.x = 0.0f;
    }
}

void Player::setName(std::string name) {
	this->name = name;
}

std::string Player::getName() {
	return this->name;
}

void Player::setHealth(int16_t health) {
	this->health = health;
}

int16_t Player::getHealth() {
	return this->health;
}

