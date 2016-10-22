#include <SFML/Graphics.hpp>
#include "bird.h"
#include "background.h"
#include "interface.h"

static const int RESOLUTION_W = 480;
static const int RESOLUTION_H = 640;

const float SPEED = 160.f; // pixels per second.

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

void update(sf::Clock &clock, Background &background, Bird &bird)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	float moveSpeed  = SPEED * elapsedTime;

	clock.restart();
	if (bird.jumping == STARTED)
	{
		birdJump(elapsedTime, bird);
	}
	moveGround(moveSpeed, background.ground);
}

void render(sf::RenderWindow &window, const Bird &bird, Background &background, Interface &gui)
{
	window.clear(SKY_COLOR);
	window.draw(background.wrapper);
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
	if (!initializeBird(bird))
		return(EXIT_FAILURE);
	Background background;
	if (!initializeBackground(background))
		return EXIT_FAILURE;
	Interface gui;
	if (!initializeInterface(gui))
		return EXIT_FAILURE;

	sf::Clock clock;

	while (window.isOpen())
	{
		handleEvents(window, bird);
		update(clock, background, bird);
		render(window, bird, background, gui);
	}

	return 0;
}