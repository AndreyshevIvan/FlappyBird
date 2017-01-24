#pragma once
#include "stdafx.h"
#include "bird.h"

static const sf::Vector2f BIRD_SIZE = { 50 , 35 };
static const sf::Vector2i BIRD_IMAGE_SIZE = { 34 , 24 };
static const sf::Vector2f BIRD_POSITION = { 80, 320 };
static const float COLLISION_SHAPE_RADIUS = BIRD_SIZE.y / 2.3f;

static const float G = 12;
static const float JUMP_HEIGHT = 64;
static const float JUMP_SPEED = sqrt((2.0f * JUMP_HEIGHT) / G);
static const float IMPULSE = 200;
static const float MAX_BIRD_HEIGHT = -BIRD_SIZE.y;

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
	m_body.setOrigin(BIRD_SIZE * 0.5f);

	m_collisionShape.setRadius(COLLISION_SHAPE_RADIUS);
	m_collisionShape.setOrigin(COLLISION_SHAPE_RADIUS, COLLISION_SHAPE_RADIUS);
}

void Bird::Init()
{
	status = BirdStatus::IDLE;

	m_body.setPosition(BIRD_POSITION);
	m_body.setRotation(0);
	m_collisionShape.setPosition(BIRD_POSITION);

	m_jumpSpeed = 0;
	m_flappingAnimTime = 0;
	m_idleAnimTime = 0;
}

void Bird::FlappingAnimate(float elapsedTime)
{
	m_flappingAnimTime += FLAPPING_SPEED * elapsedTime;

	if (static_cast<int>(m_flappingAnimTime) > 2)
	{
		m_flappingAnimTime = 0;
	}

	int frame = static_cast<int>(m_flappingAnimTime);
	sf::IntRect textureArea(frame * BIRD_IMAGE_SIZE.x, 0, BIRD_IMAGE_SIZE.x, BIRD_IMAGE_SIZE.y);
	m_body.setTextureRect(textureArea);
}

void Bird::Idle(float elapsedTime)
{
	const float PI = static_cast<float>(M_PI);

	m_idleAnimTime += elapsedTime;
	if (m_idleAnimTime >= 2 * PI)
	{
		m_idleAnimTime = 0;
	}
	m_body.move(0, OSCILLATION_AMPLITUDE * sin(FLAPPING_SPEED * m_idleAnimTime));
}

void Bird::Draw(sf::RenderWindow& window)
{
	window.draw(m_body);
}

void Bird::Jump()
{
	status = BirdStatus::FLAPPING;
	m_jumpSpeed = -JUMP_SPEED;
}

void Bird::Update(float elapsedTime)
{
	if (status == BirdStatus::IDLE)
	{
		Idle(elapsedTime);
	}
	else if (status == BirdStatus::FLAPPING)
	{
		UpdateGravity(elapsedTime);
	}

	FlappingAnimate(elapsedTime);
}

void Bird::UpdateGravity(float elapsedTime)
{
	float movement = m_jumpSpeed;

	m_jumpSpeed = m_jumpSpeed + G * elapsedTime;
	movement = m_jumpSpeed * elapsedTime;

	if (m_body.getPosition().y < MAX_BIRD_HEIGHT)
	{
		m_body.setPosition(BIRD_POSITION.x, MAX_BIRD_HEIGHT);
	}

	m_body.move(0, IMPULSE * movement);
	m_collisionShape.setPosition(m_body.getPosition());

	RotateBody(elapsedTime, movement);
}

void Bird::RotateBody(float elapsedTime, float movement)
{
	if (movement < 0)
	{
		m_body.setRotation(UP_ROT_ANGALE);
	}
	else if (m_body.getRotation() != DOWN_ROT_ANGLE)
	{
		m_body.rotate(DOWN_ROT_SPEED * elapsedTime);
		const float bodyRotation = m_body.getRotation();

		if (bodyRotation < 360 + UP_ROT_ANGALE && bodyRotation > DOWN_ROT_ANGLE)
		{
			m_body.setRotation(DOWN_ROT_ANGLE);
		}
	}
}