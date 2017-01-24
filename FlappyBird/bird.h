#pragma once
#include "stdafx.h"

enum struct BirdStatus
{
	IDLE,
	FLAPPING,
};

struct Bird
{
	Bird();

	BirdStatus status;

	float m_jumpSpeed;

	sf::RectangleShape m_body;
	sf::Texture m_bodyTexture;
	sf::CircleShape m_collisionShape;

	float m_flappingAnimTime;
	float m_idleAnimTime;

	void Init();

	void Jump();

	void FlappingAnimate(float elapsedTime);
	void Idle(float elapsedTime);

	void Update(float elapsedTime);
	void UpdateGravity(float elapsedTime);
	void RotateBody(float elapsedTime, float movement);

	void Draw(sf::RenderWindow& window);
};