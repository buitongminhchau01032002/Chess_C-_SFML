#include "Pawn.h"



Pawn::Pawn() {
	this->type = 'P';
	this->numOfMoves = 0;
}
Pawn::Pawn(char color) {
	this->type = 'P';
	this->numOfMoves = 0;
	this->color = color;
}
Pawn::Pawn(char color, Pos pos) {
	this->type = 'P';
	this->numOfMoves = 0;
	this->color = color;
	this->pos = pos;
	if (color == 'w')
		this->texture.loadFromFile("img/pawn_w.png");
	else
		this->texture.loadFromFile("img/pawn_b.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->pos.getCoord());
}

// Hàm kiểm tra việc di chuyển đến vị trí đích có hợp lệ hay không
bool Pawn::validateMove(Piece*** board, Pos moveToPos) {
	int fromCol = pos.getCol();
	int fromRow = pos.getRow();
	int toCol = moveToPos.getCol();
	int toRow = moveToPos.getRow();

	if (pos == moveToPos) // Vị trí ô nguồn trùng vị trí ô đích
		return false;

	// Quân cờ tại ô nguồn cùng màu với quân cờ tại ô đích
	if (board[toRow][toCol] != NULL)
		if (board[toRow][toCol]->getColor() == color)
			return false;
	// Chỉ có thể đi thẳng ăn chéo

	if ((toCol != pos.getCol()) &&
		(toCol != pos.getCol() - 1) &&
		(toCol != pos.getCol() + 1))
		return false;



	// Quân cờ chỉ có thể tiến thẳng nhưng không thể ăn
	if (toCol == pos.getCol())
	{
		if (board[pos.getRow()][pos.getCol()]->getColor() == 'w')
		{
			if (board[pos.getRow()][pos.getCol()]->getNumOfMoves() != 0)
			{
				if (toRow == pos.getRow() + 1 &&
					board[pos.getRow() + 1][pos.getCol()] == NULL)
					return true;
			}
			else
			{
				if (toRow == pos.getRow() + 1 &&
					board[pos.getRow() + 1][pos.getCol()] == NULL)
					return true;
				if (toRow == pos.getRow() + 2)
					if (board[pos.getRow() + 1][pos.getCol()] == NULL &&
						board[pos.getRow() + 2][pos.getCol()] == NULL)
						return true;
			}

		}
		if (board[pos.getRow()][pos.getCol()]->getColor() == 'b')
		{
			if (board[pos.getRow()][pos.getCol()]->getNumOfMoves() != 0)
			{
				if (toRow == pos.getRow() - 1 &&
					board[pos.getRow() - 1][pos.getCol()] == NULL)
					return true;
			}
			else
			{
				if (toRow == pos.getRow() - 1 &&
					board[pos.getRow() - 1][pos.getCol()] == NULL)
					return true;
				if (toRow == pos.getRow() - 2)
					if (board[pos.getRow() - 1][pos.getCol()] == NULL &&
						board[pos.getRow() - 2][pos.getCol()] == NULL)
						return true;
			}
		}
	}
	// Quân cờ chỉ có thể ăn chéo
	if ((toCol == pos.getCol() - 1) ||
		(toCol == pos.getCol() + 1))
	{
		if (board[pos.getRow()][pos.getCol()]->getColor() == 'b' &&
			toRow == pos.getRow() - 1 &&
			board[toRow][toCol] != NULL)
			return true;
		if (board[pos.getRow()][pos.getCol()]->getColor() == 'w' &&
			toRow == pos.getRow() + 1 &&
			board[toRow][toCol] != NULL)
			return true;
	}


	return false;
}

