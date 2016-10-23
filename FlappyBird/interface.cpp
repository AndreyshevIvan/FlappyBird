#include "interface.h"
#include <SFML/Graphics.hpp>
#include <iostream>

static const float RESOLUTION_W = 480;

static const int FONT_SIZE = 50;
static const sf::Vector2f POINTS_POS = { RESOLUTION_W / 2.0f, 0 };

bool initializeInterface(Interface &gui)
{
	if (!gui.pointsFont.loadFromFile("resources/FlappyBird.otf"))
		return false;

	sf::Text startPoints("0", gui.pointsFont, FONT_SIZE);
	std::cout << gui.pointsText.getGlobalBounds().width;
	gui.pointsText = startPoints;
	gui.pointsText.setOrigin(12.5, 0);
	gui.pointsText.setFillColor(sf::Color::White);
	gui.pointsText.setPosition(POINTS_POS);

	return true;
}

int addPoint(Interface &gui)
{
	return 0;
}