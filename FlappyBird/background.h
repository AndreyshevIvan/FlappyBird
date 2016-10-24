#pragma once
#include <SFML/Graphics.hpp>
#include "bird.h"
#include "interface.h"

static const sf::Color SKY_COLOR = sf::Color(0, 153, 204);
static const int GROUNDS_COUNT = 3;
static const int TUBES_COUNT = 3;

struct Background
{
	sf::RectangleShape ground[GROUNDS_COUNT];
	sf::RectangleShape wrapper;
	sf::Texture groundTexture;
	sf::Texture wrapperTexture;
	sf::RectangleShape tubes[TUBES_COUNT][2];
	sf::Texture tubeTextureBottom;
	sf::Texture tubeTextureTop;
	bool tubeStatus[TUBES_COUNT];
};

bool initializeBackground(Background &background);
bool inititalizeWrapper(Background &background);
bool inititalizeGround(Background &background);
void moveGround(const float &moveSpeed, sf::RectangleShape ground[]);
void drawGround(sf::RenderWindow &window, sf::RectangleShape ground[]);
bool inititalizeTubes(Background &background);
void moveTubes(const float &moveSpeed, Background &background, Bird &bird, Interface &gui);
void drawTubes(sf::RenderWindow &window, Background &background);
void guideAnimate(Interface &gui);