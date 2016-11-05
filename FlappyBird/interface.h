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

bool initInterface(Interface &gui);
bool loadGuiFiles(Interface &gui);
void initPoints(Interface &gui);
void initScore(Interface &gui);
void initStatistic(Interface &gui);
void initPressR(Interface &gui);
void initGuide(Interface &gui);
void initGameName(Interface &gui);
void initGameOver(Interface &gui);
void initSound(Interface &gui);
void addPoint(Interface &gui);
void stayingInterfaceAnimate(float elapsedTime, Interface &gui);