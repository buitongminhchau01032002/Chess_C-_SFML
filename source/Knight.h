#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
// Qu�n m�
class Knight : public Piece {
public:
	Knight();
	Knight(char color);
	Knight(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};
