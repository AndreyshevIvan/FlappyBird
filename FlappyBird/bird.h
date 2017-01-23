#pragma once
#include "stdafx.h"
#include "interface.h"
#include "background.h"

struct Bird
{
	Bird();

	std::vector<float> jumpingVector; // {time, past height}

	sf::RectangleShape m_body;
	sf::Texture m_bodyTexture;
	sf::CircleShape m_collisionShape;

	float m_flappingAnimTime;
	float m_idleAnimTime;

	void Init();
};

void startJump(Bird &bird, Interface &gui);
void birdJump(const float &elapsedTime, Bird &bird);
void flappingAnimate(Bird &bird, const float &elapsedTime);
void stayingAnimate(Bird &bird, const float &elapsedTime);