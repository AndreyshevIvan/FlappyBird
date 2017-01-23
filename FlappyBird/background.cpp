#pragma once
#include <SFML/Graphics.hpp>
#include "background.h"
#include "interface.h"
#include "bird.h"

static const float RESOLUTION_W = 480;
static const float RESOLUTION_H = 640;

static const sf::Vector2f GROUND_SIZE = { RESOLUTION_W, 70 };
static const sf::Vector2f TUBE_SIZE = { 52, 400 };
static const sf::Vector2f WRAPPER_SIZE = { RESOLUTION_W, 125 };

static const float GROUND_OFFSET = 446;
static const float TUBES_OFFSET = RESOLUTION_W / 2;
static const float INIT_OFFSET = RESOLUTION_W + 200;
static const float VERTICAL_OFFSET = 60;

static const sf::Vector2f WRAPPER_POS = { 0, RESOLUTION_H - GROUND_SIZE.y - WRAPPER_SIZE.y };
static const sf::Vector2f GROUND_POS = { 0, RESOLUTION_H - GROUND_SIZE.y };

static const float TUBE_GAP = 150;

static const int MIN_TUBE_HEIGHT = (int)(TUBE_GAP + VERTICAL_OFFSET);
static const int MAX_TUBE_HEIGHT = (int)(RESOLUTION_H - GROUND_SIZE.y - VERTICAL_OFFSET);

const float SPEED = 250.f; // pixels per second.


void Background::Init()
{
	srand((unsigned)time(NULL));

	InitWrapper();
	InitGround();
	InitTubes();
}

void Background::InitWrapper()
{
	wrapperTexture.loadFromFile("resources/wrapper.png");

	wrapper = sf::RectangleShape(WRAPPER_SIZE);
	wrapper.setTexture(&wrapperTexture);
	wrapper.setPosition(WRAPPER_POS);
}

void Background::InitGround()
{
	groundTexture.loadFromFile("resources/ground.png");

	for (size_t ground = 0; ground < GROUNDS_COUNT; ground++)
	{
		sf::RectangleShape groundBlock;
		groundBlock.setSize(GROUND_SIZE);
		groundBlock.setTexture(&groundTexture);
		groundBlock.setPosition(GROUND_OFFSET * ground, GROUND_POS.y);

		grounds.push_back(groundBlock);
	}
}

void Background::InitTubes()
{
	tubes.clear();
	tubesStatuses.clear();

	tubeTextureBottom.loadFromFile("resources/tubeBottom.png");
	tubeTextureTop.loadFromFile("resources/tubeTop.png");

	for (int tubesNumber = 0; tubesNumber < TUBES_COUNT; tubesNumber++)
	{
		sf::RectangleShape bottomTube;
		sf::RectangleShape topTube;

		int randomHeight = MIN_TUBE_HEIGHT + rand() % (MAX_TUBE_HEIGHT - MIN_TUBE_HEIGHT);

		bottomTube = sf::RectangleShape(TUBE_SIZE);
		bottomTube.setTexture(&tubeTextureBottom);
		bottomTube.setOrigin(TUBE_SIZE.x / 2.0f, 0);
		bottomTube.setPosition((INIT_OFFSET + (float)tubesNumber * TUBES_OFFSET), (float)randomHeight);

		topTube = bottomTube;
		topTube.rotate(180);
		topTube.setTexture(&tubeTextureTop);
		topTube.setPosition(bottomTube.getPosition().x, bottomTube.getPosition().y - TUBE_GAP);

		tubes.push_back(bottomTube);
		tubes.push_back(topTube);
	}

	for (size_t status = 0; status < TUBES_COUNT / 2; status++)
	{
		tubesStatuses.push_back(false);
	}
}

void Background::Update(float elapsedTime)
{
	UpdateGround(elapsedTime);
	UpdateTubes(elapsedTime);
}

void Background::UpdateGround(float elapsedTime)
{
	const float movement = -SPEED * elapsedTime;

	for (auto ground : grounds)
	{
		const sf::Vector2f position = ground.getPosition();

		if (position.x + GROUND_SIZE.x <= 0)
			ground.setPosition(GROUND_OFFSET * GROUNDS_COUNT + position.x, position.y);

		ground.move(movement, 0);
	}
}

void Background::UpdateTubes(float elapsedTime)
{
	const float movement = -SPEED * elapsedTime;

	for (size_t tube = 0; tube < TUBES_COUNT; tube += 2)
	{
		sf::RectangleShape bottomTube = tubes[tube];
		sf::RectangleShape topTube = tubes[tube + 1];

		if (bottomTube.getPosition().x + TUBE_SIZE.x / 2.0f <= 0)
		{
			int randomHeight = rand() % (MAX_TUBE_HEIGHT - MIN_TUBE_HEIGHT) + MIN_TUBE_HEIGHT;

			bottomTube.setPosition(bottomTube.getPosition().x + (TUBES_OFFSET * (float)TUBES_COUNT / 2.0f), (float)randomHeight);
			topTube.setPosition(bottomTube.getPosition().x, bottomTube.getPosition().y - TUBE_GAP);

			tubes[tube].setPosition(bottomTube.getPosition());
			tubes[tube + 1].setPosition(topTube.getPosition());

			if (tube % 2 == 0)
				tubesStatuses[tube / 2] = false;
		}
		tubes[tube].move(movement, 0);
		tubes[tube + 1].move(movement, 0);
	}
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(wrapper);

	for (auto tube : tubes)
		window.draw(tube);

	for (auto ground : grounds)
		window.draw(ground);
}