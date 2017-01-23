#pragma once
#include "stdafx.h"
#include "interface.h"
#include "background.h"

struct Bird
{
	Bird();

	std::vector<float> jumpingVector; // {time, past height}

	sf::RectangleShape body;
	sf::Texture bodyTexture;
	sf::CircleShape collisionShape;

	float flappingAnimTime;
	float idleAnimTime;

	void Init();
};

void isTubeChecked(Bird &bird, Background &background, Interface &gui);
bool collision(Bird &bird, Background background);
void startJump(Bird &bird, Interface &gui);
void birdJump(const float &elapsedTime, Bird &bird);
void flappingAnimate(Bird &bird, const float &elapsedTime);
void stayingAnimate(Bird &bird, const float &elapsedTime);