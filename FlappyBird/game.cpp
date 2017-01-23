#include "stdafx.h"
#include "game.h"

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

bool Game::IsBirdCollide()
{
	auto birdBody = bird.m_collisionShape.getGlobalBounds();

	for (auto tube : background.tubes)
		if (birdBody.intersects(tube.getGlobalBounds()))
			return true;

	for (auto ground : background.grounds)
		if (birdBody.intersects(ground.getGlobalBounds()))
			return true;

	return false;
}

void Game::CheckBirdCollide()
{
	if (IsBirdCollide())
	{
		gui.failSound.play();
		initScore(gui);
		m_currentScene = &m_finishScene;
	}
}

void Game::CheckTubeComplete()
{
	for (size_t tube = 0; tube < background.tubes.size(); tube += 2)
	{
		const float birdPos = bird.m_body.getPosition().x;
		const float tubePos = background.tubes[tube].getPosition().x;

		if (tubePos <= birdPos && !background.tubesStatuses[tube])
		{
			background.tubesStatuses[tube] = true;
			addPoint(gui);
		}
	}
}