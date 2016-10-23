#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bird.h"
#include "background.h"
#include "interface.h"
#include <iostream>

static const int RESOLUTION_W = 480;
static const int RESOLUTION_H = 640;

const float SPEED = 250.f; // pixels per second.

void handleEvents(sf::RenderWindow &window, Bird &bird)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			startJump(bird);
		}
	}
}

bool startGame(Bird &bird, Background &background, Interface &gui)
{
	srand(time(NULL));
	if (!initializeBird(bird))
		return(EXIT_FAILURE);
	if (!initializeBackground(background))
		return EXIT_FAILURE;
	if (!initializeInterface(gui))
		return EXIT_FAILURE;

	return true;
}

bool collision(Bird &bird, Background background, Interface &gui)
{
	for (int groundNumber = 0; groundNumber < GROUNDS_COUNT; groundNumber++)
	{
		if (bird.shape.getGlobalBounds().intersects(background.ground[groundNumber].getGlobalBounds()))
		{
			startGame(bird, background, gui);
			return true;
		}
	}

	for (int tubeNumber = 0; tubeNumber < TUBES_COUNT; tubeNumber++)
	{
		if (
			bird.shape.getGlobalBounds().intersects(background.tubes[tubeNumber][0].getGlobalBounds()) ||
			bird.shape.getGlobalBounds().intersects(background.tubes[tubeNumber][1].getGlobalBounds())
			)
		{
			startGame(bird, background, gui);
			return true;
		}
	}

	return false;
}

void update(sf::Clock &clock, Background &background, Bird &bird, Interface &gui)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	float moveSpeed = SPEED * elapsedTime;
	clock.restart();

	if (collision(bird, background, gui))
		startGame(bird, background, gui);

	animateBird(bird, elapsedTime);

	

	if (bird.jumping == STARTED)
	{
		birdJump(elapsedTime, bird);
		moveTubes(moveSpeed, background, bird, gui);
	}
	moveGround(moveSpeed, background.ground);
}

void render(sf::RenderWindow &window, const Bird &bird, Background &background, Interface &gui)
{
	window.clear(SKY_COLOR);
	window.draw(background.wrapper);
	drawTubes(window, background);
	drawGround(window, background.ground);
	window.draw(gui.pointsText);
	window.draw(bird.shape);
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Flappy Bird", sf::Style::Titlebar + sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	Bird bird;
	Background background;
	Interface gui;

	startGame(bird, background, gui);

	sf::Clock clock;

	while (window.isOpen())
	{
		handleEvents(window, bird);
		update(clock, background, bird, gui);
		render(window, bird, background, gui);
	}

	return 0;
}