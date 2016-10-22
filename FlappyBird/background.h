#pragma once
#include <SFML/Graphics.hpp>

struct Background
{
	sf::RectangleShape ground[3];
	sf::RectangleShape wrapper;
	sf::Texture groundTexture;
	sf::Texture wrapperTexture;
};

bool initializeBackground(Background &background);
bool inititalizeWrapper(Background &background);
bool inititalizeGround(Background &background);
bool drawGround(sf::RenderWindow &window, sf::RectangleShape ground[]);
void moveGround(float &moveSpeed, sf::RectangleShape ground[]);