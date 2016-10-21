#include <SFML/Graphics.hpp>
#include "bird.h"
#include "background.h"

static const int RESOLUTION_W = 480;
static const int RESOLUTION_H = 640;

static const sf::Color SKY_COLOR = sf::Color(0, 153, 204);

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

void update(sf::Clock &clock)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();
}

void render(sf::RenderWindow &window, const Bird &bird, const Background &background)
{
	window.clear(SKY_COLOR);
	window.draw(background.wrapper);
	window.draw(bird.shape);
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Flappy Bird");

	Bird bird;
	initializeBird(bird);
	Background background;
	initializeBackground(background);

	while (window.isOpen())
	{
		handleEvents(window);
		render(window, bird, background);
	}
}