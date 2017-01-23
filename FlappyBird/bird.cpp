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
	m_bodyTexture.loadFromFile("resources/mainHero.png");

	m_body.setSize(BIRD_SIZE);
	m_body.setTexture(&m_bodyTexture);
	m_body.setTextureRect(sf::IntRect(40, 0, 40, 28));
	m_body.setOrigin(BIRD_SIZE.x / 2.0f, BIRD_SIZE.y / 2.0f);

	m_collisionShape.setRadius(COLLISION_SHAPE_RADIUS);
	m_collisionShape.setOrigin(COLLISION_SHAPE_RADIUS, COLLISION_SHAPE_RADIUS);
}

void Bird::Init()
{
	m_body.setPosition(BIRD_POSITION);
	m_body.setRotation(0);
	m_collisionShape.setPosition(BIRD_POSITION);

	jumpingVector = { 0, 0 }; // {time, past height}
	m_flappingAnimTime = 0;
	m_idleAnimTime = 0;
}

void flappingAnimate(Bird &bird, const float &elapsedTime)
{
	bird.m_flappingAnimTime += FLAPPING_SPEED * elapsedTime;
	if ((int)bird.m_flappingAnimTime > 2)
		bird.m_flappingAnimTime = 0;
	bird.m_body.setTextureRect(sf::IntRect((int)bird.m_flappingAnimTime * 34, 0, 34, 24));
}

void stayingAnimate(Bird &bird, const float &elapsedTime)
{
	const float PI = float(M_PI);

	bird.m_idleAnimTime += 1 * elapsedTime;
	if (bird.m_idleAnimTime >= 2 * PI)
		bird.m_idleAnimTime = 0;
	bird.m_body.move(0, OSCILLATION_AMPLITUDE * sin(FLAPPING_SPEED * bird.m_idleAnimTime));
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

	if (bird.m_body.getPosition().y < ROOF)
		bird.m_body.setPosition(BIRD_POSITION.x, ROOF);

	if (movement < 0)
		bird.m_body.setRotation(UP_ROT_ANGALE);
	else if (bird.m_body.getRotation() != DOWN_ROT_ANGLE)
	{
		bird.m_body.rotate(DOWN_ROT_SPEED * elapsedTime);
		if (bird.m_body.getRotation() < 360 + UP_ROT_ANGALE && bird.m_body.getRotation() > DOWN_ROT_ANGLE)
			bird.m_body.setRotation(DOWN_ROT_ANGLE);
	}

	bird.m_body.move(0, IMPULSE * movement);
	bird.m_collisionShape.setPosition(bird.m_body.getPosition());
}