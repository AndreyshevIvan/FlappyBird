#include <SFML/Graphics.hpp>
#include "bird.h"

const int RESOLUTION_W = 480;
const int RESOLUTION_H = 640;

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

void render(sf::RenderWindow &window, const Bird &bird)
{
	window.clear();
	window.draw(bird.shape);
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Flappy Bird");

	Bird bird;
	initializeBird(bird);

	while (window.isOpen())
	{
		handleEvents(window);
		render(window, bird);
	}
}