#include <SFML/Graphics.hpp>
#include "background.h"

static const sf::Vector2f WRAPPER_SIZE = { 480, 230 };
static const sf::Vector2f WRAPPER_POS = { 0, 320 };

bool initializeBackground(Background &background)
{
	if (!background.wrapperTexture.loadFromFile("resources/wrapper.png"))
		return EXIT_FAILURE;
	background.wrapper = sf::RectangleShape(WRAPPER_SIZE);
	background.wrapper.setTexture(&background.wrapperTexture);
	background.wrapper.setPosition(WRAPPER_POS);

	return true;
}