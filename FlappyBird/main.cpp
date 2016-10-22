#include <SFML/Graphics.hpp>
#include "bird.h"
#include "background.h"

static const int RESOLUTION_W = 480;
static const int RESOLUTION_H = 640;

static const sf::Color SKY_COLOR = sf::Color(0, 153, 204);

const float SPEED = 160.f; // pixels per second.

void handleEvents(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

float calculateMoveSpeed(sf::Clock &clock)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	const float STEP = SPEED * elapsedTime;

	return STEP;
}

void update(sf::Clock &clock, Background &background)
{
	float moveSpeed = calculateMoveSpeed(clock);
	clock.restart();
	moveGround(moveSpeed, background.ground);
}

void render(sf::RenderWindow &window, const Bird &bird, Background &background)
{
	window.clear(SKY_COLOR);
	window.draw(background.wrapper);
	drawGround(window, background.ground);
	window.draw(bird.shape);
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Flappy Bird");

	Bird bird;
	if (!initializeBird(bird))
		return(EXIT_FAILURE);
	Background background;
	if (!initializeBackground(background))
		return EXIT_FAILURE;

	sf::Clock clock;

	while (window.isOpen())
	{
		handleEvents(window);
		update(clock, background);
		render(window, bird, background);
	}

	return 0;
}