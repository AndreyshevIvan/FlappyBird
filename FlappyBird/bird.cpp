#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bird.h"
#include <cmath>

static const sf::Vector2f BIRD_SIZE = { 50 , 35 };
static const sf::Vector2f BIRD_POSITION = { 80, 320 };
static const float COLLISION_SHAPE_RADIUS = BIRD_SIZE.y / 2.3f;

static const float G = 12;
static const float JUMP_HEIGHT = 70;
static const float JUMP_SPEED = sqrt((2.0f * JUMP_HEIGHT) / G);
static const float IMPULSE = 200;
static const float ROOF = -BIRD_SIZE.y;

static const float UP_ROT_ANGALE = -50;
static const float DOWN_ROT_ANGLE = 90;
static const float DOWN_ROT_SPEED = 280;

static const float FLAPPING_SPEED = 15;
static const float OSCILLATION_AMPLITUDE = 0.12f;

Bird::Bird()
{
	bodyTexture.loadFromFile("resources/mainHero.png");

	body.setSize(BIRD_SIZE);
	body.setTexture(&bodyTexture);
	body.setTextureRect(sf::IntRect(40, 0, 40, 28));
	body.setOrigin(BIRD_SIZE.x / 2.0f, BIRD_SIZE.y / 2.0f);

	collisionShape.setRadius(COLLISION_SHAPE_RADIUS);
	collisionShape.setOrigin(COLLISION_SHAPE_RADIUS, COLLISION_SHAPE_RADIUS);
}

void Bird::Init()
{
	body.setPosition(BIRD_POSITION);
	body.setRotation(0);
	collisionShape.setPosition(BIRD_POSITION);

	jumpingVector = { 0, 0 }; // {time, past height}
	flappingAnimTime = 0;
	idleAnimTime = 0;
}

bool collision(Bird &bird, Background background)
{
	auto collisionShape = bird.collisionShape.getGlobalBounds();
	for (int number = 0; number < GROUNDS_COUNT; number++)
		if
			(
				collisionShape.intersects(background.tubes[number][0].getGlobalBounds()) ||
				collisionShape.intersects(background.tubes[number][1].getGlobalBounds()) ||
				collisionShape.intersects(background.ground[number].getGlobalBounds())
				)
			return true;

	return false;
}

void isTubeChecked(Bird &bird, Background &background, Interface &gui)
{
	for (int tubeNumber = 0; tubeNumber < TUBES_COUNT; tubeNumber++)
		if (background.tubes[tubeNumber][0].getPosition().x <= bird.body.getPosition().x && !background.tubeStatus[tubeNumber])
		{
			background.tubeStatus[tubeNumber] = true;
			addPoint(gui);
		}
}

void flappingAnimate(Bird &bird, const float &elapsedTime)
{
	bird.flappingAnimTime += FLAPPING_SPEED * elapsedTime;
	if ((int)bird.flappingAnimTime > 2)
		bird.flappingAnimTime = 0;
	bird.body.setTextureRect(sf::IntRect((int)bird.flappingAnimTime * 34, 0, 34, 24));
}

void stayingAnimate(Bird &bird, const float &elapsedTime)
{
	const float PI = float(M_PI);

	bird.idleAnimTime += 1 * elapsedTime;
	if (bird.idleAnimTime >= 2 * PI)
		bird.idleAnimTime = 0;
	bird.body.move(0, OSCILLATION_AMPLITUDE * sin(FLAPPING_SPEED * bird.idleAnimTime));
}

void startJump(Bird &bird, Interface &gui)
{
	gui.wingSound.play();
	bird.jumpingVector = { 0, 0 };
}

void birdJump(const float &elapsedTime, Bird &bird)
{
	float time = bird.jumpingVector[0] += elapsedTime;
	float pastHeight = bird.jumpingVector[1];
	float height;
	float movement;

	bird.jumpingVector[1] = height = JUMP_SPEED * time - 0.5f * G * pow(time, 2.0f);
	movement = pastHeight - height;

	if (bird.body.getPosition().y < ROOF)
		bird.body.setPosition(BIRD_POSITION.x, ROOF);

	if (movement < 0)
		bird.body.setRotation(UP_ROT_ANGALE);
	else if (bird.body.getRotation() != DOWN_ROT_ANGLE)
	{
		bird.body.rotate(DOWN_ROT_SPEED * elapsedTime);
		if (bird.body.getRotation() < 360 + UP_ROT_ANGALE && bird.body.getRotation() > DOWN_ROT_ANGLE)
			bird.body.setRotation(DOWN_ROT_ANGLE);
	}

	bird.body.move(0, IMPULSE * movement);
	bird.collisionShape.setPosition(bird.body.getPosition());
}