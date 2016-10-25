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
	std::vector<float> jumpingVector; // {time, past height}
	sf::RectangleShape shape;
	sf::CircleShape collisionShape;
	sf::Texture shapeTexture;
	float animTime[2];
};

bool initializeBird(Bird &bird);
bool initializeBody(Bird &bird);
void initializeCollisionShape(Bird &bird);
void startJump(Bird &bird, Interface &gui);
void birdJump(const float &elapsedTime, Bird &bird);
void flappingAnimate(Bird &bird, const float &elapsedTime);
void stayingAnimate(Bird &bird, const float &elapsedTime);