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


Background::Background()
{
	Init();
}

void Background::Init()
{
	initWrapper(*this);
	initGround(*this);
	initTubes(*this);
	for (auto tube = 0; tube < TUBES_COUNT; tube++)
		tubeStatus[tube] = false;
}

bool initWrapper(Background &background)
{
	if (!background.wrapperTexture.loadFromFile("resources/wrapper.png"))
		return false;
	background.wrapper = sf::RectangleShape(WRAPPER_SIZE);
	background.wrapper.setTexture(&background.wrapperTexture);
	background.wrapper.setPosition(WRAPPER_POS);

	return true;
}

bool initGround(Background &background)
{
	srand((unsigned)time(NULL));

	if (!background.groundTexture.loadFromFile("resources/ground.png"))
		return false;
	for (int groundNumber = 0; groundNumber < GROUNDS_COUNT; groundNumber++)
	{
		background.ground[groundNumber] = sf::RectangleShape(GROUND_SIZE);
		background.ground[groundNumber].setTexture(&background.groundTexture);
		background.ground[groundNumber].setPosition(GROUND_OFFSET * groundNumber, GROUND_POS.y);
	}

	return true;
}

bool initTubes(Background &background)
{
	if (!background.tubeTextureBottom.loadFromFile("resources/tubeBottom.png"))
		return false;
	if (!background.tubeTextureTop.loadFromFile("resources/tubeTop.png"))
		return false;
	for (int tubesNumber = 0; tubesNumber < TUBES_COUNT; tubesNumber++)
	{
		sf::RectangleShape bottomTube;
		sf::RectangleShape topTube;

		int randomHeight = MIN_TUBE_HEIGHT + rand() % (MAX_TUBE_HEIGHT - MIN_TUBE_HEIGHT);

		bottomTube = sf::RectangleShape(TUBE_SIZE);
		bottomTube.setTexture(&background.tubeTextureBottom);
		bottomTube.setOrigin(TUBE_SIZE.x / 2.0f, 0);
		bottomTube.setPosition((float)(INIT_OFFSET + tubesNumber * TUBES_OFFSET), (float)randomHeight);

		topTube = bottomTube;
		topTube.rotate(180);
		topTube.setTexture(&background.tubeTextureTop);
		topTube.setPosition(bottomTube.getPosition().x, bottomTube.getPosition().y - TUBE_GAP);

		background.tubes[tubesNumber][0] = bottomTube;
		background.tubes[tubesNumber][1] = topTube;
	}

	return true;
}

void drawGround(sf::RenderWindow &window, sf::RectangleShape ground[])
{
	for (int groundNumber = 0; groundNumber < GROUNDS_COUNT; groundNumber++)
		window.draw(ground[groundNumber]);
}

void moveGround(float &elapsedTime, sf::RectangleShape ground[])
{
	const float moveSpeed = SPEED * elapsedTime;

	for (int groundNumber = 0; groundNumber < GROUNDS_COUNT; groundNumber++)
	{
		if (ground[groundNumber].getPosition().x + GROUND_SIZE.x <= 0)
			ground[groundNumber].setPosition(ground[groundNumber].getPosition().x + (GROUND_OFFSET * GROUNDS_COUNT), GROUND_POS.y);
		ground[groundNumber].move(-moveSpeed, 0);
	}
}

void drawTubes(sf::RenderWindow &window, Background &background)
{
	for (int tubeNumber = 0; tubeNumber < TUBES_COUNT; tubeNumber++)
	{
		window.draw(background.tubes[tubeNumber][0]);
		window.draw(background.tubes[tubeNumber][1]);
	}
}

void moveTubes(float &elapsedTime, Background &background)
{
	const float moveSpeed = SPEED * elapsedTime;

	for (int tubeNumber = 0; tubeNumber < TUBES_COUNT; tubeNumber++)
	{
		sf::RectangleShape bottomTube = background.tubes[tubeNumber][0];
		sf::RectangleShape topTube = background.tubes[tubeNumber][1];
		if (bottomTube.getPosition().x + TUBE_SIZE.x / 2.0f <= 0)
		{
			int randomHeight = rand() % (MAX_TUBE_HEIGHT - MIN_TUBE_HEIGHT) + MIN_TUBE_HEIGHT;

			bottomTube.setPosition(bottomTube.getPosition().x + (TUBES_OFFSET * (float)TUBES_COUNT), (float)randomHeight);
			topTube.setPosition(bottomTube.getPosition().x, bottomTube.getPosition().y - TUBE_GAP);

			background.tubes[tubeNumber][0].setPosition(bottomTube.getPosition());
			background.tubes[tubeNumber][1].setPosition(topTube.getPosition());

			background.tubeStatus[tubeNumber] = false;
		}
		background.tubes[tubeNumber][0].move(-moveSpeed, 0);
		background.tubes[tubeNumber][1].move(-moveSpeed, 0);
	}
}