#pragma once
#include <SFML/Graphics.hpp>

struct Bird
{
	sf::CircleShape shape;
};

bool initializeBird(Bird &bird);
void birdJump(Bird &bird);