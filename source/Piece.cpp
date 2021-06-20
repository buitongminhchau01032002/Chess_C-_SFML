#include "Piece.h"

char Piece::getColor() {
	return color;
}
char Piece::getType() {
	return type;
}
void Piece::setPos(Pos pos) {
	this->pos = pos;
}
void Piece::addNumOfMoves() {
	numOfMoves++;
}

int Piece::getNumOfMoves() {
	return numOfMoves;
}

void Piece::setNumOfMoves(int n) {
	numOfMoves = n;
}

void Piece::update() {
	this->sprite.setPosition(pos.getCoord());
}
void Piece::render(sf::RenderTarget* target) {
	target->draw(this->sprite);
}