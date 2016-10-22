#include <SFML/Graphics.hpp>
#include "background.h"

static const sf::Vector2f GROUND_SIZE = { 480, 90 };
static const sf::Vector2f GROUND_POS = { 0, 640 - GROUND_SIZE.y };
static const sf::Vector2f GROUND_OFFSET = { 439, 0 };
static const sf::Vector2f WRAPPER_SIZE = { 480, 125 };
static const sf::Vector2f WRAPPER_POS = { 0, 640 - GROUND_SIZE.y - WRAPPER_SIZE.y };

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
	for (int groundNumber = 0; groundNumber < 3; groundNumber++)
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

bool drawGround(sf::RenderWindow &window, const sf::RectangleShape ground[])
{
	for (int groundNumber = 0; groundNumber < 3; groundNumber++)
	{
		window.draw(ground[groundNumber]);
	}

	return true;
}