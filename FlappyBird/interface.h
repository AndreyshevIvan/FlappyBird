#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

struct Interface
{
	sf::Font pointsFont;
	sf::Text points;
	sf::Text score;
	sf::Text pressR;
	sf::Music pointSound;
	sf::Music wingSound;
	sf::Music failSound;
	sf::Music tenPointsSound;
	sf::RectangleShape statistic;
	sf::RectangleShape guide;
	sf::RectangleShape gameName;
	sf::RectangleShape gameOver;
	sf::Texture statisticTexture;
	sf::Texture guideTexture;
	sf::Texture gameNameTexture;
	sf::Texture gameOverTexture;
	int pointsCount;
	float guideTimer;
};

template <typename T>
std::string toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

bool initializeInterface(Interface &gui);
bool loadGuiFiles(Interface &gui);
void initializePoints(Interface &gui);
void initializeScore(Interface &gui);
void initializeStatistic(Interface &gui);
void initializePressR(Interface &gui);
void initializeGuide(Interface &gui);
void initializeGameName(Interface &gui);
void initializeGameOver(Interface &gui);
void initializeSound(Interface &gui);
void addPoint(Interface &gui);
void stayingInterfaceAnimate(float elapsedTime, Interface &gui);