#pragma once
#include <SFML/Graphics.hpp>

static const sf::Color SKY_COLOR = sf::Color(0, 153, 204);
static const int GROUNDS_COUNT = 3;
static const int TUBES_COUNT = 6;

struct Background
{
	Background();

	std::vector<sf::RectangleShape> grounds;
	std::vector<sf::RectangleShape> tubes;
	std::vector<bool> tubesStatuses;

	sf::RectangleShape wrapper;
	sf::Texture groundTexture;
	sf::Texture wrapperTexture;
	sf::Texture tubeTextureBottom;
	sf::Texture tubeTextureTop;

	void Init();
};

bool initWrapper(Background &background);
bool initGround(Background &background);
void moveGround(float &elapsedTime, std::vector<sf::RectangleShape>& grounds);
void drawGround(sf::RenderWindow &window, std::vector<sf::RectangleShape> const& grounds);
bool initTubes(Background &background);
void moveTubes(float &elapsedTIme, Background &background);
void drawTubes(sf::RenderWindow &window, Background &background);