#include "King.h"
#include <cmath>


King::King() {
	this->type = 'K';
	this->numOfMoves = 0;
}
King::King(char color) {
	this->type = 'K';
	this->numOfMoves = 0;
	this->color = color;
}
King::King(char color, Pos pos) {
	this->type = 'K';
	this->numOfMoves = 0;
	this->color = color;
	this->pos = pos;
	if (color == 'w')
		this->texture.loadFromFile("img/king_w.png");
	else
		this->texture.loadFromFile("img/king_b.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->pos.getCoord());
}

// Hàm kiểm tra việc di chuyển đến vị trí đích có hợp lệ hay không
bool King::validateMove(Piece*** board, Pos moveToPos) {
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

	// Vua di chuyển theo từng ô ngang, dọc, chéo
	if (abs(fromCol-toCol)<=1 && abs(fromRow-toRow)<=1)
		return true;

	return false;
}

