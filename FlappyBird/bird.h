#pragma once
#include <SFML/Graphics.hpp>

enum Jumping
{
	STARTED,
	NOT_STARTED
};

struct Bird
{
	Jumping jumping;
	std::vector<float> jumpingVector; // {speed, time, past height}
	sf::RectangleShape shape;
	sf::Texture shapeTexture;
};

bool initializeBird(Bird &bird);
void startJump(Bird &bird);
void birdJump(const float &elapsedTime, Bird &bird);