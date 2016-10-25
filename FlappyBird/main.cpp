#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bird.h"
#include "background.h"
#include "interface.h"

static const int RESOLUTION_W = 480;
static const int RESOLUTION_H = 640;

const float SPEED = 250.f; // pixels per second.

bool initializeGame(Bird &bird, Background &background, Interface &gui)
{
	if (!initializeBird(bird))
		exit(1);
	if (!initializeBackground(background))
		exit(1);
	if (!initializeInterface(gui))
		exit(1);

	return true;
}

void handleEvents(sf::RenderWindow &window, Bird &bird, Background &background, Interface &gui)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && bird.status != GAME_PAUSED)
		{
			startJump(bird, gui);
			bird.status = PLAYING;
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && bird.status == GAME_PAUSED)
			initializeGame(bird, background, gui);
	}
}

bool collision(Bird &bird, Background background)
{
	auto collisionShape = bird.collisionShape.getGlobalBounds();
	for (int number = 0; number < GROUNDS_COUNT; number++)
	{
		if
			(
				collisionShape.intersects(background.tubes[number][0].getGlobalBounds()) ||
				collisionShape.intersects(background.tubes[number][1].getGlobalBounds()) ||
				collisionShape.intersects(background.ground[number].getGlobalBounds())
				)
			return true;
	}

	return false;
}

void isTubeChecked(Bird &bird, Background &background, Interface &gui)
{
	for (int tubeNumber = 0; tubeNumber < TUBES_COUNT; tubeNumber++)
	{
		if (background.tubes[tubeNumber][0].getPosition().x <= bird.shape.getPosition().x && !background.tubeStatus[tubeNumber])
		{
			background.tubeStatus[tubeNumber] = true;
			addPoint(gui);
		}
	}
}

void update(sf::Clock &clock, Background &background, Bird &bird, Interface &gui)
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
		moveTubes(moveSpeed, background);
		isTubeChecked(bird, background, gui);
		if (collision(bird, background))
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
	window.draw(bird.shape);
	switch (bird.status)
	{
	case NOT_STARTED:
		window.draw(gui.gameName);
		window.draw(gui.guide);
		break;
	case PLAYING:
		window.draw(gui.points);
		break;
	case GAME_PAUSED:
		window.draw(gui.statistic);
		window.draw(gui.score);
		window.draw(gui.gameOver);
		window.draw(gui.pressR);
		break;
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

	srand((unsigned)time(NULL));
	initializeGame(bird, background, gui);

	while (window.isOpen())
	{
		handleEvents(window, bird, background, gui);
		update(clock, background, bird, gui);
		render(window, bird, background, gui);
	}

	return 0;
}