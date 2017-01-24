#pragma once
#include "stdafx.h"

static const sf::Color SKY_COLOR = sf::Color(0, 153, 204);
static const int GROUNDS_COUNT = 3;
static const int TUBES_COUNT = 6;

struct Background
{
	std::vector<sf::RectangleShape> grounds;
	std::vector<sf::RectangleShape> tubes;
	std::vector<bool> tubesStatuses;

	sf::RectangleShape wrapper;
	sf::Texture groundTexture;
	sf::Texture wrapperTexture;
	sf::Texture tubeTextureBottom;
	sf::Texture tubeTextureTop;

	void Init();
	void InitWrapper();
	void InitGround();
	void InitTubes();

	void Update(float elapsedTime);
	void UpdateGround(float elapsedTime);
	void UpdateTubes(float elapsedTime);

	void Draw(sf::RenderWindow& window);
};