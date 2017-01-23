#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "background.h"
#include "interface.h"
#include <iostream>

static const float RESOLUTION_W = 480;
static const float RESOLUTION_H = 640;

static const sf::Vector2f STATISTIC_SIZE = { 300, 150 };
static const sf::Vector2f GUIDE_SIZE = { 150, 156 };
static const sf::Vector2f GAME_NAME_SIZE = { 250, 67 };
static const sf::Vector2f GAME_OVER_SIZE = { 192, 42 };

static const sf::Vector2f STATISTIC_POS = { RESOLUTION_W / 2.0f, RESOLUTION_H / 2.0f };
static const sf::Vector2f GUIDE_POS = { 120, 325 };
static const sf::Vector2f POINTS_POS = { RESOLUTION_W / 2.0f, 20 };
static const sf::Vector2f SCORE_POS = { (RESOLUTION_W + STATISTIC_SIZE.x) / 2.0f - 25, RESOLUTION_H / 2.0f - STATISTIC_SIZE.y / 4.3f};
static const sf::Vector2f FONT_PRESS_R_POS = { RESOLUTION_W / 2.0f, STATISTIC_POS.y + 90 };

static const unsigned int FONT_POINTS_SIZE = 40;
static const unsigned int FONT_SCORE_SIZE = 30;
static const unsigned int FONT_PRESS_R_SIZE = 18;
static const unsigned int FONT_OUTLINE_THICKNESS_4 = 4;
static const unsigned int FONT_OUTLINE_THICKNESS_2 = 2;
static const sf::Color FONT_COLOR = sf::Color(250, 250, 250);
static const sf::Color FONT_OUTLINE_COLOR = sf::Color(92, 53, 70);

static const float FLAPPING_SPEED = 15;
static const float OSCILLATION_AMPLITUDE = 0.12f;

static const int POINTS_TO_WIN = 1000;


Interface::Interface()
{
	Init();
}

void Interface::Init()
{
	loadGuiFiles(*this);
	initPoints(*this);
	initStatistic(*this);
	initPressR(*this);
	initGuide(*this);
	initGameName(*this);
	initGameOver(*this);
	initSound(*this);
}

bool loadGuiFiles(Interface &gui)
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

void initPoints(Interface &gui) 
{
	sf::Text startPoints("0", gui.pointsFont, FONT_POINTS_SIZE);
	gui.points = startPoints;
	gui.points.setOutlineColor(FONT_OUTLINE_COLOR);
	gui.points.setOutlineThickness((float)FONT_OUTLINE_THICKNESS_4);
	gui.points.setFillColor(FONT_COLOR);
	gui.points.setOrigin(gui.points.getGlobalBounds().width / 2.0f, 0);
	gui.points.setPosition(POINTS_POS);
	gui.pointsCount = 0;
}

void initScore(Interface &gui)
{
	sf::Text startPoints("0", gui.pointsFont, FONT_SCORE_SIZE);

	gui.score = startPoints;
	gui.score.setOutlineColor(FONT_OUTLINE_COLOR);
	gui.score.setOutlineThickness((float)FONT_OUTLINE_THICKNESS_2);
	gui.score.setFillColor(FONT_COLOR);
	gui.score.setString(std::to_string(gui.pointsCount));
	gui.score.setOrigin(gui.score.getGlobalBounds().width, 0);
	gui.score.setPosition(SCORE_POS);
}

void initPressR(Interface &gui)
{
	sf::Text startPoints("PRESS 'R' TO RESTART", gui.pointsFont, FONT_PRESS_R_SIZE);

	gui.pressR = startPoints;
	gui.pressR.setOutlineColor(FONT_OUTLINE_COLOR);
	gui.pressR.setOutlineThickness((float)FONT_OUTLINE_THICKNESS_2);
	gui.pressR.setFillColor(FONT_COLOR);
	gui.pressR.setOrigin(gui.pressR.getGlobalBounds().width / 2.0f, 0);
	gui.pressR.setPosition(FONT_PRESS_R_POS);
}

void initStatistic(Interface &gui)
{
	gui.statistic.setSize(STATISTIC_SIZE);
	gui.statistic.setTexture(&gui.statisticTexture);
	gui.statistic.setOrigin(STATISTIC_SIZE.x / 2.0f, STATISTIC_SIZE.y / 2.0f);
	gui.statistic.setPosition(RESOLUTION_W / 2.0f, RESOLUTION_H / 2.0f);
}

void initGuide(Interface &gui)
{
	gui.guide.setSize(GUIDE_SIZE);
	gui.guide.setTexture(&gui.guideTexture);
	gui.guide.setOrigin(0, gui.guide.getGlobalBounds().height / 2.0f);
	gui.guide.setPosition(GUIDE_POS);
	gui.guideTimer = 0;
}

void initGameName(Interface &gui)
{
	gui.gameName.setSize(GAME_NAME_SIZE);
	gui.gameName.setOrigin(GAME_NAME_SIZE.x / 2.0f, GAME_NAME_SIZE.y / 2.0f);
	gui.gameName.setPosition(RESOLUTION_W / 2.0f, 100);
	gui.gameName.setTexture(&gui.gameNameTexture);
}

void initGameOver(Interface &gui)
{
	gui.gameOver.setSize(GAME_OVER_SIZE);
	gui.gameOver.setOrigin(GAME_OVER_SIZE.x / 2.0f, GAME_OVER_SIZE.y / 2.0f);
	gui.gameOver.setPosition(RESOLUTION_W / 2.0f, STATISTIC_POS.y - STATISTIC_SIZE.y);
	gui.gameOver.setTexture(&gui.gameOverTexture);
}

void addPoint(Interface &gui)
{
	gui.pointsCount += 1;
	gui.pointSound.play();
	if (gui.pointsCount >= POINTS_TO_WIN)
		exit(1);

	gui.points.setString(std::to_string(gui.pointsCount));
	gui.points.setOrigin(gui.points.getGlobalBounds().width / 2.0f, 0);
	gui.points.setPosition(POINTS_POS);
}

void initSound(Interface &gui)
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