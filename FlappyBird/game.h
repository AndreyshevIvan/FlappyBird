#pragma once
#include "stdafx.h"

#include "bird.h"
#include "background.h"
#include "interface.h"

struct GameScene
{
	std::function<void()> onUpdate;
	std::function<void(sf::Event& event)> toHandle;
	std::function<void(sf::RenderWindow& window)> onDraw;
};

struct Game
{
	sf::Clock clock;
	float m_elapsedTime;

	Bird bird;
	Background background;
	Interface gui;

	GameScene m_startScene;
	GameScene m_gameplayScene;
	GameScene m_finishScene;
	GameScene *m_currentScene = nullptr;

	void Init();
	void CalculateTime();
};

void Game::Init()
{
	bird.Init();
	background.Init();
	gui.Init();
}

void Game::CalculateTime()
{
	m_elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();
}