#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

struct Interface
{
	sf::Font pointsFont;
	sf::Text pointsText;
	int pointsCount;
};

template <typename T>
std::string toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

bool initializeInterface(Interface &gui);
int addPoint(Interface &gui);