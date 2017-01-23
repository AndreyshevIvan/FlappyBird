#pragma once
#include <SFML/Graphics.hpp>

static const sf::Color SKY_COLOR = sf::Color(0, 153, 204);
static const int GROUNDS_COUNT = 3;
static const int TUBES_COUNT = 3;

struct Background
{
	Background();

	sf::RectangleShape ground[GROUNDS_COUNT];
	sf::RectangleShape tubes[TUBES_COUNT][2];
	sf::RectangleShape wrapper;
	sf::Texture groundTexture;
	sf::Texture wrapperTexture;
	sf::Texture tubeTextureBottom;
	sf::Texture tubeTextureTop;
	bool tubeStatus[TUBES_COUNT];

	void Init();
};

bool initWrapper(Background &background);
bool initGround(Background &background);
void moveGround(float &elapsedTime, sf::RectangleShape ground[]);
void drawGround(sf::RenderWindow &window, sf::RectangleShape ground[]);
bool initTubes(Background &background);
void moveTubes(float &elapsedTIme, Background &background);
void drawTubes(sf::RenderWindow &window, Background &background);