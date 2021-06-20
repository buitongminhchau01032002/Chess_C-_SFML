#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
// Quân tốt
class Pawn : public Piece {
public:
	Pawn();
	Pawn(char color);
	Pawn(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};


