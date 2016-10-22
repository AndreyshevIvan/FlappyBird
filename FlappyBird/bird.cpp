#include <SFML/Graphics.hpp>
#include "bird.h"
#include <cmath>

static const sf::Vector2f BIRD_SIZE = { 60 , 64 };
static const sf::Vector2f BIRD_POSITION = { 50, 320 };

static const float JUMP_HEIGHT = 70;
static const float G = 8;
static const float IMPULSE = 100;

bool initializeBird(Bird &bird)
{
	bird.jumping = NOT_STARTED;
	bird.jumpingVector = {0, 0, 0}; // {speed, time, past height}
	bird.shape.setSize(BIRD_SIZE);
	if (!bird.shapeTexture.loadFromFile("resources/MainHero.png"))
		return EXIT_FAILURE;
	bird.shape.setTexture(&bird.shapeTexture);
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

	bird.shape.move(0, IMPULSE * movement);
}