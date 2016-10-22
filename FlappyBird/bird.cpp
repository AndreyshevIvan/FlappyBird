#include <SFML/Graphics.hpp>
#include "bird.h"

static const sf::Color BIRD_COLOR = sf::Color(255, 216, 0);
static const float BIRD_SPEED = 20.f; // pixels per second.
static const float BIRD_RADIUS = 20.f; // pixels
static const sf::Vector2f BIRD_POSITION = { 50, 320 }; // pixels.

bool initializeBird(Bird &bird)
{
	bird.shape.setRadius(BIRD_RADIUS);
	bird.shape.setFillColor(BIRD_COLOR);
	bird.shape.setPosition(BIRD_POSITION);

	return true;
}

void birdJump(Bird &bird)
{
	sf::Vector2f position = bird.shape.getPosition();
	position.y -= 10.0f;
	bird.shape.setPosition(position);
}