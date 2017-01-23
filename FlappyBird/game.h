#pragma once
#include "stdafx.h"

#include "bird.h"
#include "background.h"
#include "interface.h"
#include "sound.h"

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
	FBSound sound;

	GameScene m_startScene;
	GameScene m_gameplayScene;
	GameScene m_finishScene;
	GameScene *m_currentScene = nullptr;

	void Init();
	void CalculateTime();

	bool IsBirdFell();
	void CheckBirdCollide();

	void CheckTubeComplete();
};