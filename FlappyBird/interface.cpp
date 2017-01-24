#pragma once
#include "stdafx.h"
#include "interface.h"

static const sf::Vector2f RESOLUTION = {480, 640};

static const sf::Vector2f STATISTIC_BAR_SIZE = { 300, 150 };
static const sf::Vector2f GUIDE_SIZE = { 150, 156 };
static const sf::Vector2f GAME_NAME_SIZE = { 250, 67 };
static const sf::Vector2f GAME_OVER_SIZE = { 192, 42 };

static const sf::Vector2f STATISTIC_POS = RESOLUTION * 0.5f;
static const sf::Vector2f GUIDE_PANEL_POS = { 120, 325 };
static const sf::Vector2f POINTS_POS = { RESOLUTION.x / 2.0f, 20 };
static const sf::Vector2f SCORE_POS = { (RESOLUTION.x + STATISTIC_BAR_SIZE.x) / 2.0f - 25, RESOLUTION.y / 2.0f - STATISTIC_BAR_SIZE.y / 4.3f};
static const sf::Vector2f FONT_PRESS_R_POS = { RESOLUTION.x / 2.0f, STATISTIC_POS.y + 90 };

static const unsigned int FONT_POINTS_SIZE = 40;
static const unsigned int FONT_SCORE_SIZE = 30;
static const unsigned int FONT_PRESS_R_SIZE = 18;
static const unsigned int FONT_OUTLINE_THICKNESS_4 = 4;
static const unsigned int FONT_OUTLINE_THICKNESS_2 = 2;
static const sf::Color FONT_COLOR = sf::Color(250, 250, 250);
static const sf::Color FONT_OUTLINE_COLOR = sf::Color(92, 53, 70);

static const float FLAPPING_SPEED = 15;
static const float OSCILLATION_AMPLITUDE = 0.12f;

static const int POINTS_TO_WIN = 1000;


Interface::Interface()
{
	LoadFiles();
	Init();
}

void Interface::Init()
{
	InitPoints();
	InitGameNamePanel();
	InitStatisticPanel();
	InitScore();
	InitHelpText();
	InitGuidePanel();
	InitGameOverPanel();
}

void Interface::LoadFiles()
{
	m_pointsFont.loadFromFile("resources/FlappyBird.otf");
	m_statisticPanelTexture.loadFromFile("resources/gameOverMenu.png");
	m_guideTexture.loadFromFile("resources/guide.png");
	m_gameNameTexture.loadFromFile("resources/gameName.png");
	m_gameOverTexture.loadFromFile("resources/gameOver.png");
}

void Interface::InitPoints()
{
	m_pointsCount = 0;
	sf::Text startPoints(std::to_string(m_pointsCount), m_pointsFont, FONT_POINTS_SIZE);
	m_points = startPoints;
	m_points.setOutlineColor(FONT_OUTLINE_COLOR);
	m_points.setOutlineThickness((float)FONT_OUTLINE_THICKNESS_4);
	m_points.setFillColor(FONT_COLOR);
	m_points.setOrigin(m_points.getGlobalBounds().width / 2.0f, 0);
	m_points.setPosition(POINTS_POS);
}

void Interface::InitScore()
{
	sf::Text startPoints("0", m_pointsFont, FONT_SCORE_SIZE);
	m_score = startPoints;
	m_score.setOutlineColor(FONT_OUTLINE_COLOR);
	m_score.setOutlineThickness((float)FONT_OUTLINE_THICKNESS_2);
	m_score.setFillColor(FONT_COLOR);
	m_score.setString(std::to_string(m_pointsCount));
	m_score.setOrigin(m_score.getGlobalBounds().width, 0);
	m_score.setPosition(SCORE_POS);
}

void Interface::InitHelpText()
{
	sf::Text startPoints("PRESS 'R' TO RESTART", m_pointsFont, FONT_PRESS_R_SIZE);
	m_helpText = startPoints;
	m_helpText.setOutlineColor(FONT_OUTLINE_COLOR);
	m_helpText.setOutlineThickness((float)FONT_OUTLINE_THICKNESS_2);
	m_helpText.setFillColor(FONT_COLOR);
	m_helpText.setOrigin(m_helpText.getGlobalBounds().width / 2.0f, 0);
	m_helpText.setPosition(FONT_PRESS_R_POS);
}

void Interface::InitStatisticPanel()
{
	m_statisticPanel.setSize(STATISTIC_BAR_SIZE);
	m_statisticPanel.setTexture(&m_statisticPanelTexture);
	m_statisticPanel.setOrigin(STATISTIC_BAR_SIZE * 0.5f);
	m_statisticPanel.setPosition(RESOLUTION * 0.5f);
}

void Interface::InitGuidePanel()
{
	m_guide.setSize(GUIDE_SIZE);
	m_guide.setTexture(&m_guideTexture);
	m_guide.setOrigin(0, m_guide.getGlobalBounds().height / 2.0f);
	m_guide.setPosition(GUIDE_PANEL_POS);
	m_guideTimer = 0;
}

void Interface::InitGameNamePanel()
{
	m_gameName.setSize(GAME_NAME_SIZE);
	m_gameName.setOrigin(GAME_NAME_SIZE * 0.5f);
	m_gameName.setPosition(RESOLUTION.x / 2.0f, 100);
	m_gameName.setTexture(&m_gameNameTexture);
}

void Interface::InitGameOverPanel()
{
	m_gameOver.setSize(GAME_OVER_SIZE);
	m_gameOver.setOrigin(GAME_OVER_SIZE * 0.5f);
	m_gameOver.setPosition(RESOLUTION.x / 2.0f, STATISTIC_POS.y - STATISTIC_BAR_SIZE.y);
	m_gameOver.setTexture(&m_gameOverTexture);
}

void Interface::AddPoint()
{
	m_pointsCount = (m_pointsCount < POINTS_TO_WIN) ? m_pointsCount += 1 : 0;
}

void Interface::Update(int scene, float elapsedTime)
{
	if (scene == START)
	{
		UpdateIdleInterface(elapsedTime);
	}
	else if (scene == GAMEPLAY)
	{
		m_score.setString(std::to_string(m_pointsCount));

		m_points.setString(std::to_string(m_pointsCount));
		m_points.setOrigin(m_points.getGlobalBounds().width / 2.0f, 0);
		m_points.setPosition(POINTS_POS);
	}
}

void Interface::UpdateIdleInterface(float elapsedTime)
{
	const float PI = float(M_PI);

	m_guideTimer += elapsedTime;
	if (m_guideTimer >= 2 * PI)
		m_guideTimer = 0;
	m_guide.move(0, OSCILLATION_AMPLITUDE * sin(FLAPPING_SPEED * m_guideTimer));
	m_gameName.move(0, OSCILLATION_AMPLITUDE * sin(FLAPPING_SPEED * m_guideTimer));
}

void Interface::Draw(int scene, sf::RenderWindow& window)
{
	switch (scene)
	{
	case START:
		window.draw(m_gameName);
		window.draw(m_guide);
		break;
	case GAMEPLAY:
		window.draw(m_points);
		break;
	case GAMEOVER:
		window.draw(m_statisticPanel);
		window.draw(m_gameOver);
		window.draw(m_score);
		window.draw(m_helpText);
		break;
	default:
		break;
	}
}