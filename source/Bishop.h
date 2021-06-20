#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
class Bishop : public Piece {
public:
	Bishop();
	Bishop(char color);
	Bishop(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};
