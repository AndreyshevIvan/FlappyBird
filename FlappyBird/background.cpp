#include <SFML/Graphics.hpp>
#include "background.h"

static const float RESOLUTION_W = 480;
static const float RESOLUTION_H = 640;

static const sf::Vector2f GROUND_SIZE = { RESOLUTION_W, 90 };
static const sf::Vector2f GROUND_POS = { 0, RESOLUTION_H - GROUND_SIZE.y };
static const sf::Vector2f GROUND_OFFSET = { 439, 0 };
static const sf::Vector2f WRAPPER_SIZE = { RESOLUTION_W, 125 };
static const sf::Vector2f WRAPPER_POS = { 0, RESOLUTION_H - GROUND_SIZE.y - WRAPPER_SIZE.y };


bool inititalizeWrapper(Background &background)
{
	if (!background.wrapperTexture.loadFromFile("resources/wrapper.png"))
		return false;
	background.wrapper = sf::RectangleShape(WRAPPER_SIZE);
	background.wrapper.setTexture(&background.wrapperTexture);
	background.wrapper.setPosition(WRAPPER_POS);

	return true;
}

bool inititalizeGround(Background &background)
{
	if (!background.groundTexture.loadFromFile("resources/ground.png"))
		return EXIT_FAILURE;
	for (int groundNumber = 0; groundNumber < GROUNDS_COUNT; groundNumber++)
	{
		background.ground[groundNumber] = sf::RectangleShape(GROUND_SIZE);
		background.ground[groundNumber].setTexture(&background.groundTexture);
		background.ground[groundNumber].setPosition(GROUND_POS.x + GROUND_OFFSET.x * groundNumber, GROUND_POS.y);
	}

	return true;
}

bool initializeBackground(Background &background)
{
	if (!inititalizeWrapper(background) || !inititalizeGround(background))
		return EXIT_FAILURE;

	return true;
}

bool drawGround(sf::RenderWindow &window, sf::RectangleShape ground[])
{
	for (int groundNumber = 0; groundNumber < GROUNDS_COUNT; groundNumber++)
	{
		window.draw(ground[groundNumber]);
	}

	return true;
}

void moveGround(float &moveSpeed, sf::RectangleShape ground[])
{
	for (int groundNumber = 0; groundNumber < GROUNDS_COUNT; groundNumber++)
	{
		if ((ground[groundNumber].getPosition().x + GROUND_SIZE.x) <= 0)
			ground[groundNumber].setPosition(ground[groundNumber].getPosition().x + (GROUND_OFFSET.x * GROUNDS_COUNT), GROUND_POS.y);
		ground[groundNumber].move(-moveSpeed, 0);
	}
}