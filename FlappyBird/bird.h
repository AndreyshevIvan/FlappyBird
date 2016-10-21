#pragma once
#include <SFML/Graphics.hpp>

enum struct Direction
{
	NONE,
	JUMP
};

struct Bird
{
	sf::CircleShape shape;
	Direction direction;
};

void initializeBird(Bird &bird);