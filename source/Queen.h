#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
// Quân hậu
class Queen : public Piece {
public:
	Queen();
	Queen(char color);
	Queen(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};
