#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "background.h"
#include "interface.h"
#include <iostream>

static const float RESOLUTION_W = 480;

static const int FONT_SIZE = 40;
static const sf::Vector2f POINTS_POS = { RESOLUTION_W / 2.0f, 20 };
static const int FONT_THICKNESS = 4;

static const sf::Vector2f STATISTIC_SIZE = { 300, 150 };

bool initializeInterface(Interface &gui)
{
	if (!gui.pointsFont.loadFromFile("resources/FlappyBird.otf"))
		return false;
	if (!gui.statisticTexture.loadFromFile("resources/gameOverMenu.png"))
		return false;

	sf::Text startPoints("0", gui.pointsFont, FONT_SIZE);
	gui.pointsText = startPoints;
	gui.pointsText.setOrigin(gui.pointsText.getCharacterSize() / 4.0, 0);
	gui.pointsText.setOutlineColor(sf::Color::Black);
	gui.pointsText.setOutlineThickness(FONT_THICKNESS);
	gui.pointsText.setFillColor(sf::Color::White);
	gui.pointsText.setPosition(POINTS_POS);
	gui.pointsCount = 0;
	gui.statistic.setSize(STATISTIC_SIZE);
	gui.statistic.setOrigin(gui.statistic.getGlobalBounds().width / 2.0f, gui.statistic.getGlobalBounds().height / 2.0f);
	gui.statistic.setPosition(RESOLUTION_W / 2.0f, -STATISTIC_SIZE.y);
	gui.statistic.setTexture(&gui.statisticTexture);
	createSound(gui);

	return true;
}

int addPoint(Interface &gui)
{
	gui.pointsCount += 1;
	gui.pointSound.play();
	if (gui.pointsCount > 1000)
		return EXIT_FAILURE;
	if (gui.pointsCount > 9 && gui.pointsCount < 100)
	{
		gui.pointsText.setOrigin(gui.pointsText.getCharacterSize() / 2.0f, 0);
	}
	if (gui.pointsCount > 1000)
	{
		gui.pointsText.setOrigin(gui.pointsText.getCharacterSize() * 0.8f, 0);
	}
	gui.pointsText.setString(toString(gui.pointsCount));

	return 0;
}

bool createSound(Interface &gui)
{
	if (!gui.pointSound.openFromFile("resources/Sounds/point.ogg"))
		return EXIT_FAILURE;
	if (!gui.wingSound.openFromFile("resources/Sounds/sfx_wing.ogg"))
		return EXIT_FAILURE;
	if (!gui.failSound.openFromFile("resources/Sounds/hit.ogg"))
		return EXIT_FAILURE;
	if (!gui.ost.openFromFile("resources/Sounds/OST.ogg"))
		return EXIT_FAILURE;

	gui.pointSound.setVolume(60);
	gui.wingSound.setVolume(50);
	gui.failSound.setVolume(40);
	gui.ost.setVolume(30);

	return true;
}