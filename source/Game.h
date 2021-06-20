#pragma once
#include "constValue.h"
#include <SFML/Graphics.hpp>
#include "Board.h"

class Game {
private:
	// variable
	sf::RenderWindow* window;
	// function
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	Board* board;
public:
	// constructor, destructor
	Game();
	~Game(void);
	// function
	void run();
};

