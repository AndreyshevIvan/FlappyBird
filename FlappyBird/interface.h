#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

struct Interface
{
	sf::Font pointsFont;
	sf::Text pointsText;
	int pointsCount;
	sf::Music pointSound;
	sf::Music wingSound;
	sf::Music failSound;
	sf::Music tenPointsSound;
	sf::Music ost;
	sf::RectangleShape statistic;
	sf::Texture statisticTexture;
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
bool createSound(Interface &gui);