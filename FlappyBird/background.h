#pragma once
#include <SFML/Graphics.hpp>

struct Background
{
	sf::RectangleShape ground[3];
	sf::RectangleShape wrapper;
	sf::Texture groundTexture;
	sf::Texture wrapperTexture;
};

bool initializeBackground(Background &baclground);