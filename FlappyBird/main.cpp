#include "stdafx.h"
#include "game.h"

static const int RESOLUTION_W = 480;
static const int RESOLUTION_H = 640;
static const std::string GAME_NAME = "Flappy Bird";

void InitScenes(Game& game);
void InitStartScene(Game &system);
void InitGameplayScene(Game& game);
void IninFinishScene(Game& game);

void EnterGameLoop(Game& game, sf::RenderWindow& window);
void Render(Game& game, sf::RenderWindow& window);
void Update(Game& game);
void HandleEvents(Game& game, sf::RenderWindow& window);

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), GAME_NAME, sf::Style::Titlebar + sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	Game flappyBird;
	flappyBird.Init();

	InitScenes(flappyBird);

	EnterGameLoop(flappyBird, window);

	return 0;
}

void EnterGameLoop(Game& game, sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		game.CalculateTime();

		HandleEvents(game, window);
		Update(game);
		Render(game, window);
	}
}

void HandleEvents(Game& game, sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) ||
			(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
			window.close();

		game.m_currentScene->toHandle(event);
	}
}

void Update(Game& game)
{
	game.m_currentScene->onUpdate();
}

void Render(Game &system, sf::RenderWindow &window)
{
	window.clear(SKY_COLOR);
	window.draw(system.background.wrapper);
	drawTubes(window, system.background);
	drawGround(window, system.background.grounds);
	window.draw(system.bird.m_body);

	system.m_currentScene->onDraw(window);

	window.display();
}

void InitScenes(Game& game)
{
	InitStartScene(game);
	InitGameplayScene(game);
	IninFinishScene(game);

	game.m_currentScene = &game.m_startScene;
}

void InitStartScene(Game& game)
{
	game.m_startScene.onUpdate = [&]() {
		flappingAnimate(game.bird, game.m_elapsedTime);
		stayingAnimate(game.bird, game.m_elapsedTime);
		stayingInterfaceAnimate(game.m_elapsedTime, game.gui);
	};

	game.m_startScene.onDraw = [&](sf::RenderWindow &window) {
		window.draw(game.gui.gameName);
		window.draw(game.gui.guide);
	};

	game.m_startScene.toHandle = [&](sf::Event &event) {
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			startJump(game.bird, game.gui);
			game.m_currentScene = &game.m_gameplayScene;
		}
	};
}

void InitGameplayScene(Game& game)
{
	game.m_gameplayScene.onUpdate = [&]() {
		flappingAnimate(game.bird, game.m_elapsedTime);
		moveGround(game.m_elapsedTime, game.background.grounds);
		birdJump(game.m_elapsedTime, game.bird);
		moveTubes(game.m_elapsedTime, game.background);
		game.CheckTubeComplete();
		game.CheckBirdCollide();
	};

	game.m_gameplayScene.onDraw = [&](sf::RenderWindow &window) {
		window.draw(game.gui.points);
	};

	game.m_gameplayScene.toHandle = [&](sf::Event & event) {
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			startJump(game.bird, game.gui);
			game.m_currentScene = &game.m_gameplayScene;
		}
	};
}

void IninFinishScene(Game& game)
{
	game.m_finishScene.onUpdate = [&]() {
	};

	game.m_finishScene.onDraw = [&](sf::RenderWindow &window) {
		window.draw(game.gui.statistic);
		window.draw(game.gui.score);
		window.draw(game.gui.gameOver);
		window.draw(game.gui.pressR);
	};

	game.m_finishScene.toHandle = [&](sf::Event &event) {
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
		{
			game.m_currentScene = &game.m_startScene;
			game.Init();
		}
	};
}