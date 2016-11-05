#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bird.h"
#include "background.h"
#include "interface.h"
#include <cassert>
#include <functional>
#include <iostream>

static const int RESOLUTION_W = 480;
static const int RESOLUTION_H = 640;

struct GameBehavior
{
	std::function<void(float dt)> onUpdate;
	std::function<void(sf::RenderWindow &window)> onDraw;
};

struct GameSystem
{
	Bird bird;
	Background background;
	Interface gui;
	sf::Clock clock;
	GameBehavior m_startBehavior;
	GameBehavior m_gameplayBehavior;
	GameBehavior m_pauseBehavior;
	GameBehavior *m_currentBehavior = nullptr;
};

void initGameStructs(Bird &bird, Background &background, Interface &gui)
{
	bool inited = initBird(bird)
		&& initBackground(background)
		&& initInterface(gui);

	if (!inited)
	{
		assert(false);
		exit(1);
	}
}

void initStartBehavior(GameSystem &system)
{
	system.m_startBehavior.onUpdate = [&](float elapsedTime) {
		flappingAnimate(system.bird, elapsedTime);
		stayingAnimate(system.bird, elapsedTime);
		stayingInterfaceAnimate(elapsedTime, system.gui);
	};
	system.m_startBehavior.onDraw = [&](sf::RenderWindow &window) {
		window.draw(system.gui.gameName);
		window.draw(system.gui.guide);
	};
}

void initGameplayBehavior(GameSystem &system)
{
	system.m_gameplayBehavior.onUpdate = [&](float elapsedTime) {
		flappingAnimate(system.bird, elapsedTime);
		moveGround(elapsedTime, system.background.ground);
		birdJump(elapsedTime, system.bird);
		moveTubes(elapsedTime, system.background);
		isTubeChecked(system.bird, system.background, system.gui);
		if (collision(system.bird, system.background))
		{
			system.gui.failSound.play();
			initScore(system.gui);
			system.m_currentBehavior = &system.m_pauseBehavior;
		}
	};
	system.m_gameplayBehavior.onDraw = [&](sf::RenderWindow &window) {
		window.draw(system.gui.points);
	};
}

void initPauseBehavior(GameSystem &system)
{
	system.m_pauseBehavior.onUpdate = [&](float elapsedTime) {
	};
	system.m_pauseBehavior.onDraw = [&](sf::RenderWindow &window) {
		window.draw(system.gui.statistic);
		window.draw(system.gui.score);
		window.draw(system.gui.gameOver);
		window.draw(system.gui.pressR);
	};
}

void initGameSystem(GameSystem &system)
{
	initGameStructs(system.bird, system.background, system.gui);
	initStartBehavior(system);
	initGameplayBehavior(system);
	initPauseBehavior(system);

	system.m_currentBehavior = &system.m_startBehavior;
}

void handleEvents(GameSystem &system, sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && system.m_currentBehavior != &system.m_pauseBehavior)
		{
			startJump(system.bird, system.gui);
			system.m_currentBehavior = &system.m_gameplayBehavior;
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && system.m_currentBehavior == &system.m_pauseBehavior)
		{
			system.m_currentBehavior = &system.m_startBehavior;
			initGameSystem(system);
		}
	}
}

void render(GameSystem &system, sf::RenderWindow &window)
{
	window.clear(SKY_COLOR);
	window.draw(system.background.wrapper);
	drawTubes(window, system.background);
	drawGround(window, system.background.ground);
	window.draw(system.bird.shape);

	system.m_currentBehavior->onDraw(window);

	window.display();
}

void enterGameLoop(GameSystem &flappyBird, sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		const float elapsedTime = flappyBird.clock.getElapsedTime().asSeconds();
		flappyBird.clock.restart();

		handleEvents(flappyBird, window);
		flappyBird.m_currentBehavior->onUpdate(elapsedTime);
		render(flappyBird, window);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Flappy Bird", sf::Style::Titlebar + sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	GameSystem flappyBird;
	initGameSystem(flappyBird);

	enterGameLoop(flappyBird, window);

	return 0;
}