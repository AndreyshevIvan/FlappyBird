#pragma once
#include <SFML/Graphics.hpp>
#include "interface.h"

enum GameStatus
{
	PLAYING,
	NOT_STARTED,
	GAME_PAUSED
};

struct Bird
{
	GameStatus status;
	std::vector<float> jumpingVector; // {speed, time, past height}
	sf::RectangleShape shape;
	sf::CircleShape collisionShape;
	sf::Texture shapeTexture;
	float animTime;
};

bool initializeBird(Bird &bird);
void startJump(Bird &bird, Interface &gui);
void birdJump(const float &elapsedTime, Bird &bird);
void animateBird(Bird &bird, const float &elapsedTime);