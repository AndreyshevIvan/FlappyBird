#pragma once
#include <SFML/Graphics.hpp>

struct Interface
{
	sf::Font pointsFont;
	sf::Text pointsText;
	int pointsCount;
};

bool initializeInterface(Interface &gui);
int addPoint(Interface &gui);