#include "Knight.h"

Knight::Knight() {
	this->type = 'N';
	this->numOfMoves = 0;
}
Knight::Knight(char color) {
	this->type = 'N';
	this->numOfMoves = 0;
	this->color = color;
}
Knight::Knight(char color, Pos pos) {
	this->type = 'N';
	this->numOfMoves = 0;
	this->color = color;
	this->pos = pos;
	if (color == 'w')
		this->texture.loadFromFile("img/knight_w.png");
	else
		this->texture.loadFromFile("img/knight_b.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->pos.getCoord());
}

// Hàm kiểm tra việc di chuyển đến vị trí đích có hợp lệ hay không
bool Knight::validateMove(Piece*** board, Pos moveToPos) {
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

	// Ô nguồn cùng cột với ô đích
	if ((toCol == (fromCol + 1)) ||
		(toCol == (fromCol - 1)))
		if ( (toRow == fromRow + 2) ||
			(toRow == fromRow - 2) )
			return true;	

	if ((toCol == (fromCol + 2)) ||
		(toCol == (fromCol - 2)))
		if ( (toRow == fromRow + 1) ||
			(toRow == fromRow - 1) )
			return true;	

	return false;
}

