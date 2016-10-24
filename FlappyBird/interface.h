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
	sf::RectangleShape statistic;
	sf::RectangleShape guide;
	float guideTimer;
	sf::RectangleShape gameName;
	sf::RectangleShape gameOver;
	sf::Texture statisticTexture;
	sf::Texture guideTexture;
	sf::Texture gameNameTexture;
	sf::Texture gameOverTexture;
};

template <typename T>
std::string toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

bool initializeInterface(Interface &gui);
bool initializeGuiFiles(Interface &gui);
void initializePoints(Interface &gui);
void initializeStatistic(Interface &gui);
void initializeGuide(Interface &gui);
void initializeGameName(Interface &gui);
void initializeGameOver(Interface &gui);
void initializeSound(Interface &gui);
bool addPoint(Interface &gui);
void centerizatePoints(Interface &gui);
void stayingInterfaceAnimate(float elapsedTime, Interface &gui);