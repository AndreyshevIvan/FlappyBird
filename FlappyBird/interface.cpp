#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "background.h"
#include "interface.h"
#include <iostream>

static const float RESOLUTION_W = 480;

static const int FONT_SIZE = 40;
static const sf::Vector2f POINTS_POS = { RESOLUTION_W / 2.0f, 20 };
static const int FONT_THICKNESS = 4;
static const sf::Color FONT_OUTLINE_COLOR = sf::Color(84, 56, 71);
static const int POINTS_TO_WIN = 100;

static const sf::Vector2f STATISTIC_SIZE = { 300, 150 };
static const sf::Vector2f GUIDE_SIZE = { 150, 156 };
static const sf::Vector2f GUIDE_POSITION = { 120, 325 };
static const sf::Vector2f GAME_NAME_SIZE = { 250, 67 };
static const sf::Vector2f GAME_OVER_SIZE = { 192, 42 };

static const float FLAPPING_SPEED = 15;
static const float OSCILLATION_AMPLITUDE = 0.12;


void initializePoints(Interface &gui)
{
	sf::Text startPoints("0", gui.pointsFont, FONT_SIZE);
	gui.pointsText = startPoints;
	gui.pointsText.setOrigin(gui.pointsText.getCharacterSize() / 4.0, 0);
	gui.pointsText.setOutlineColor(FONT_OUTLINE_COLOR);
	gui.pointsText.setOutlineThickness(FONT_THICKNESS);
	gui.pointsText.setFillColor(sf::Color::White);
	gui.pointsText.setPosition(POINTS_POS);
	gui.pointsCount = 0;
}

void initializeStatistic(Interface &gui)
{
	gui.statistic.setSize(STATISTIC_SIZE);
	gui.statistic.setOrigin(gui.statistic.getGlobalBounds().width / 2.0f, gui.statistic.getGlobalBounds().height / 2.0f);
	gui.statistic.setPosition(RESOLUTION_W / 2.0f, -STATISTIC_SIZE.y);
	gui.statistic.setTexture(&gui.statisticTexture);
}

void initializeGuide(Interface &gui)
{
	gui.guide.setSize(GUIDE_SIZE);
	gui.guide.setOrigin(0, gui.guide.getGlobalBounds().height / 2.0f);
	gui.guide.setPosition(GUIDE_POSITION);
	gui.guide.setTexture(&gui.guideTexture);
	gui.guideTimer = 0;
}

void initializeGameName(Interface &gui)
{
	gui.gameName.setSize(GAME_NAME_SIZE);
	gui.gameName.setOrigin(gui.gameName.getGlobalBounds().width / 2.0f, gui.gameName.getGlobalBounds().height / 2.0f);
	gui.gameName.setPosition(RESOLUTION_W / 2.0f, 100);
	gui.gameName.setTexture(&gui.gameNameTexture);
}

void initializeGameOver(Interface &gui)
{
	gui.gameOver.setSize(GAME_OVER_SIZE);
	gui.gameOver.setOrigin(gui.gameOver.getGlobalBounds().width / 2.0f, gui.gameOver.getGlobalBounds().height / 2.0f);
	gui.gameOver.setPosition(RESOLUTION_W / 2.0f, -GAME_OVER_SIZE.y);
	gui.gameOver.setTexture(&gui.gameOverTexture);
}

bool initializeGuiFiles(Interface &gui)
{
	if (!gui.pointsFont.loadFromFile("resources/FlappyBird.otf"))
		return false;
	if (!gui.statisticTexture.loadFromFile("resources/gameOverMenu.png"))
		return false;
	if (!gui.guideTexture.loadFromFile("resources/guide.png"))
		return false;
	if (!gui.gameNameTexture.loadFromFile("resources/gameName.png"))
		return false;
	if (!gui.gameOverTexture.loadFromFile("resources/gameOver.png"))
		return false;
	if (!gui.pointSound.openFromFile("resources/Sounds/point.ogg"))
		return false;
	if (!gui.wingSound.openFromFile("resources/Sounds/sfx_wing.ogg"))
		return false;
	if (!gui.failSound.openFromFile("resources/Sounds/hit.ogg"))
		return false;

	return true;
}

bool initializeInterface(Interface &gui)
{
	if (!initializeGuiFiles(gui))
		return false;

	initializePoints(gui);
	initializeStatistic(gui);
	initializeGuide(gui);
	initializeGameName(gui);
	initializeGameOver(gui);
	initializeSound(gui);

	return true;
}

void centerizatePoints(Interface &gui)
{
	if (gui.pointsCount > 9 && gui.pointsCount < 100)
		gui.pointsText.setOrigin(gui.pointsText.getCharacterSize() / 2.0f, 0);

	if (gui.pointsCount > 1000)
		gui.pointsText.setOrigin(gui.pointsText.getCharacterSize() * 0.8f, 0);
}

bool addPoint(Interface &gui)
{
	gui.pointsCount += 1;
	gui.pointSound.play();
	if (gui.pointsCount > POINTS_TO_WIN)
		return false;

	centerizatePoints(gui);

	gui.pointsText.setString(toString(gui.pointsCount));

	return true;
}

void initializeSound(Interface &gui)
{
	gui.pointSound.setVolume(30);
	gui.wingSound.setVolume(40);
	gui.failSound.setVolume(30);
}

void stayingInterfaceAnimate(float elapsedTime, Interface &gui)
{
	const float PI = float(M_PI);

	gui.guideTimer += elapsedTime;
	if (gui.guideTimer >= 2 * PI)
		gui.guideTimer = 0;
	gui.guide.move(0, OSCILLATION_AMPLITUDE * sin(FLAPPING_SPEED * gui.guideTimer));
	gui.gameName.move(0, OSCILLATION_AMPLITUDE * sin(FLAPPING_SPEED * gui.guideTimer));
}