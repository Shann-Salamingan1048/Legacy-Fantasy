#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class Game
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;
	Player player;
	// choose player animation phase
	uint8_t chosenPhase;
	sf::Vector2f movementsPlayer;

	void initWindow();
	void initVar();
public:
	Game();
	virtual ~Game();
	const bool isRunning() const;
	void pollEvents();

	void update();
	void render();
};

