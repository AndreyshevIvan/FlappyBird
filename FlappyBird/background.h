#pragma once
#include <SFML/Graphics.hpp>

static const sf::Color SKY_COLOR = sf::Color(0, 153, 204);
static const int GROUNDS_COUNT = 3;

struct Background
{
	sf::RectangleShape ground[GROUNDS_COUNT];
	sf::RectangleShape wrapper;
	sf::Texture groundTexture;
	sf::Texture wrapperTexture;
};

bool initializeBackground(Background &background);
bool inititalizeWrapper(Background &background);
bool inititalizeGround(Background &background);
bool drawGround(sf::RenderWindow &window, sf::RectangleShape ground[]);
void moveGround(float &moveSpeed, sf::RectangleShape ground[]);