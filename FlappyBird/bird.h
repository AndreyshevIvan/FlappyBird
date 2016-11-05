#pragma once
#include <SFML/Graphics.hpp>
#include "interface.h"
#include "background.h"

struct Bird
{
	std::vector<float> jumpingVector; // {time, past height}
	sf::RectangleShape shape;
	sf::CircleShape collisionShape;
	sf::Texture shapeTexture;
	float animTime[2];
};

bool initBird(Bird &bird);
bool initBody(Bird &bird);
void initCollisionShape(Bird &bird);
void isTubeChecked(Bird &bird, Background &background, Interface &gui);
bool collision(Bird &bird, Background background);
void startJump(Bird &bird, Interface &gui);
void birdJump(const float &elapsedTime, Bird &bird);
void flappingAnimate(Bird &bird, const float &elapsedTime);
void stayingAnimate(Bird &bird, const float &elapsedTime);