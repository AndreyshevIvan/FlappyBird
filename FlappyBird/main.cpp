#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bird.h"
#include "background.h"
#include "interface.h"
#include <iostream>

static const int RESOLUTION_W = 480;
static const int RESOLUTION_H = 640;

const float SPEED = 250.f; // pixels per second.

bool startGame(Bird &bird, Background &background, Interface &gui)
{
	if (!initializeBird(bird))
		return(EXIT_FAILURE);
	if (!initializeBackground(background))
		return EXIT_FAILURE;
	if (!initializeInterface(gui))
		return EXIT_FAILURE;

	return true;
}

void handleEvents(sf::RenderWindow &window, Bird &bird, Background &background, Interface &gui)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && bird.status != GAME_PAUSED)
		{
			startJump(bird, gui);
			bird.status = PLAYING;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && bird.status == GAME_PAUSED)
		{
			startGame(bird, background, gui);
		}
	}
}

bool collision(Bird &bird, Background background, Interface &gui)
{
	for (int number = 0; number < GROUNDS_COUNT; number++)
	{
		if 
		(
		bird.collisionShape.getGlobalBounds().intersects(background.tubes[number][0].getGlobalBounds()) ||
		bird.collisionShape.getGlobalBounds().intersects(background.tubes[number][1].getGlobalBounds()) ||
		bird.collisionShape.getGlobalBounds().intersects(background.ground[number].getGlobalBounds())
		)
			return true;
	}

	return false;
}

void update(sf::RenderWindow &window, sf::Clock &clock, Background &background, Bird &bird, Interface &gui)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	const float moveSpeed = SPEED * elapsedTime;

	clock.restart();

	switch (bird.status)
	{
	case NOT_STARTED:
		flappingAnimate(bird, elapsedTime);
		stayingAnimate(bird, elapsedTime);
		stayingInterfaceAnimate(elapsedTime, gui);
		break;
	case PLAYING:
		flappingAnimate(bird, elapsedTime);
		moveGround(moveSpeed, background.ground);
		birdJump(elapsedTime, bird);
		moveTubes(moveSpeed, background, bird, gui);
		if (collision(bird, background, gui))
		{
			gui.failSound.play();
			initializeScore(gui);
			bird.status = GAME_PAUSED;
		}
		break;
	case GAME_PAUSED:
		break;
	}
}

void render(sf::RenderWindow &window, const Bird &bird, Background &background, Interface &gui)
{
	window.clear(SKY_COLOR);
	window.draw(background.wrapper);
	drawTubes(window, background);
	drawGround(window, background.ground);
	if (bird.status == PLAYING)
		window.draw(gui.points);
	window.draw(bird.shape);
	if (bird.status == NOT_STARTED)
	{
		window.draw(gui.gameName);
		window.draw(gui.guide);
	}
	if (bird.status == GAME_PAUSED)
	{
		window.draw(gui.statistic);
		window.draw(gui.score);
		window.draw(gui.gameOver);
		window.draw(gui.pressR);
	}
		
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Flappy Bird", sf::Style::Titlebar + sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	Bird bird;
	Background background;
	Interface gui;
	sf::Clock clock;

	srand(time(NULL));
	startGame(bird, background, gui);

	while (window.isOpen())
	{
		handleEvents(window, bird, background, gui);
		update(window, clock, background, bird, gui);
		render(window, bird, background, gui);
	}

	return 0;
}