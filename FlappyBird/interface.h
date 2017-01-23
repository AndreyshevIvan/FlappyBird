#pragma once
#include "stdafx.h"

enum
{
	// Scenes
	START,
	GAMEPLAY,
	GAMEOVER,
};

struct Interface
{
	Interface();

	sf::Font m_pointsFont;

	sf::Text m_points;
	sf::Text m_score;
	sf::Text m_helpText;

	sf::RectangleShape m_statisticPanel;
	sf::RectangleShape m_guide;
	sf::RectangleShape m_gameName;
	sf::RectangleShape m_gameOver;

	sf::Texture m_statisticPanelTexture;
	sf::Texture m_guideTexture;
	sf::Texture m_gameNameTexture;
	sf::Texture m_gameOverTexture;

	int m_pointsCount;
	float m_guideTimer;

	void LoadFiles();

	void Init();
	void InitPoints();
	void InitGameNamePanel();
	void InitStatisticPanel();
	void InitScore();
	void InitHelpText();
	void InitGuidePanel();
	void InitGameOverPanel();

	void AddPoint();

	void Update(int scene, float elapsedTime);
	void UpdateIdleInterface(float elapsedTime);

	void Draw(int scene, sf::RenderWindow& window);
};