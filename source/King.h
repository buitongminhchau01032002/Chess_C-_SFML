#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
class King : public Piece {
public:
	King();
	King(char color);
	King(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};