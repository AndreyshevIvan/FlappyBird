#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "interface.h"
#include "background.h"

static const float RESOLUTION_W = 480;

static const int FONT_SIZE = 40;
static const sf::Vector2f POINTS_POS = { RESOLUTION_W / 2.0f, 20 };
static const int FONT_THICKNESS = 4;

bool initializeInterface(Interface &gui)
{
	if (!gui.pointsFont.loadFromFile("resources/FlappyBird.otf"))
		return false;

	sf::Text startPoints("0", gui.pointsFont, FONT_SIZE);
	gui.pointsText = startPoints;
	gui.pointsText.setOrigin(gui.pointsText.getCharacterSize() / 4.0, 0);
	gui.pointsText.setOutlineColor(sf::Color::Black);
	gui.pointsText.setOutlineThickness(FONT_THICKNESS);
	gui.pointsText.setFillColor(sf::Color::White);
	gui.pointsText.setPosition(POINTS_POS);
	gui.pointsCount = 0;
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
	if (!gui.failSound.openFromFile("resources/Sounds/sfx_hit.ogg"))
		return EXIT_FAILURE;
	if (!gui.ost.openFromFile("resources/Sounds/OST.ogg"))
		return EXIT_FAILURE;

	gui.pointSound.setVolume(60);
	gui.wingSound.setVolume(50);
	gui.failSound.setVolume(50);
	gui.ost.setVolume(30);

	return true;
}

void gameOverMenu(sf::RenderWindow &window, Interface &gui)
{
	bool continueFlag = false;
	while (!continueFlag)
	{
		gui.ost.stop();
		sf::Event event;

		while (!window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				
			}
		}
	}
}