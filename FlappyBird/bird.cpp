#include <SFML/Graphics.hpp>
#include "bird.h"
#include <cmath>
#include <iostream>

static const sf::Vector2f BIRD_SIZE = { 40 , 28 };
static const sf::Vector2f BIRD_POSITION = { 80, 320 };

static const float JUMP_HEIGHT = 70;
static const float G = 11;
static const float IMPULSE = 200;

static const float UP_ROT_ANGALE = -50;
static const float DOWN_ROT_ANGLE = 90;
static const float DOWN_ROT_SPEED = 0.6;

bool initializeBird(Bird &bird)
{
	bird.jumping = NOT_STARTED;
	bird.jumpingVector = {0, 0, 0}; // {speed, time, past height}
	bird.shape.setSize(BIRD_SIZE);
	if (!bird.shapeTexture.loadFromFile("resources/MainHero.png"))
		return false;
	bird.shape.setTexture(&bird.shapeTexture);
	bird.shape.setOrigin(bird.shape.getGlobalBounds().width / 2.0f, bird.shape.getGlobalBounds().height / 2.0f);
	bird.shape.setPosition(BIRD_POSITION);

	return true;
}

void startJump(Bird &bird)
{
	bird.jumping = STARTED;
	bird.jumpingVector[0] = sqrt((2.0f * JUMP_HEIGHT) / G);
	bird.jumpingVector[1] = 0;
	bird.jumpingVector[2] = 0;
}

void birdJump(const float &elapsedTime, Bird &bird)
{
	float time = bird.jumpingVector[1] += elapsedTime;
	float speed = bird.jumpingVector[0];
	float pastHeight = bird.jumpingVector[2];
	float height;
	float movement;

	bird.jumpingVector[2] = height = speed * time - 0.5f * G * pow(time, 2.0f);
	movement = pastHeight - height;
	if (bird.shape.getPosition().y < -300)
	{
		bird.shape.setPosition(BIRD_POSITION.x, -BIRD_SIZE.y);
	}

	if (movement < 0)
	{
		bird.shape.setRotation(UP_ROT_ANGALE);
	}
	else if (bird.shape.getRotation() != DOWN_ROT_ANGLE)
	{
		bird.shape.rotate(DOWN_ROT_SPEED);
		if (bird.shape.getRotation() < 360 + UP_ROT_ANGALE && bird.shape.getRotation() > DOWN_ROT_ANGLE)
			bird.shape.setRotation(DOWN_ROT_ANGLE);
	}

	bird.shape.move(0, IMPULSE * movement);
}