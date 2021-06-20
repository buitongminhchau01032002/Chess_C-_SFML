#include "Game.h"
#include <iostream>

Game::Game() {
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "King Chess");
	this->board = new Board();
}

Game::~Game(void) {
	delete this->window;
	delete board;
}

void Game::processEvents() {
	sf::Event event;
	while (this->window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::MouseButtonPressed:
			this->board->setIsClick(true);
			this->board->setMouseClickPos(event.mouseButton.x, event.mouseButton.y);
			break;
		case sf::Event::MouseButtonReleased:
			this->board->setIsClick(false);
			break;
		}
	}
}
void Game::update(sf::Time deltaTime) {
	this->board->update();
}
void Game::render() {
	this->window->clear();
	this->board->render(this->window);
	this->window->display();
}
void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f/FPS);
	while (this->window->isOpen()) {
		this->processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			this->processEvents();
			this->update(TimePerFrame);
		}
		this->render();
		if (this->board->getIsQuit())
			this->window->close();
		if (this->board->getIsReplay()) {
			delete this->board;
			this->board = new Board();
		}
	}
}