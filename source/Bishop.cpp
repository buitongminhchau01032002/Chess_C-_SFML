#include "Bishop.h"
#include <SFML/Graphics.hpp>

Bishop::Bishop() {
	this->type = 'B';
	this->numOfMoves = 0;
}
Bishop::Bishop(char color) {
	this->type = 'B';
	this->numOfMoves = 0;
	this->color = color;
}
Bishop::Bishop(char color, Pos pos) {
	this->type = 'B';
	this->numOfMoves = 0;
	this->color = color;
	this->pos = pos;
	if (color == 'w')
		this->texture.loadFromFile("img/bishop_w.png");
	else
		this->texture.loadFromFile("img/bishop_b.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->pos.getCoord());
}

// Hàm kiểm tra việc di chuyển đến vị trí đích có hợp lệ hay không
bool Bishop::validateMove(Piece*** board, Pos moveToPos) {
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

	if (fromCol == toCol ||
		fromRow == toRow)
		return false;

	//Xét ô chéo phải
	if (fromCol > toCol)
	{
		if (fromRow > toRow)
			if ((fromRow - toRow) != (fromCol - toCol))
				return false;
		if (fromRow < toRow)
			if ((toRow - fromRow) != (fromCol - toCol))
				return false;
	}
	// Xét chéo trái
	if (fromCol < toCol)
	{
		if (fromRow > toRow)
			if ((fromRow - toRow) != (toCol - fromCol))
				return false;
		if (fromRow < toRow)
			if ((toRow - fromRow) != (toCol - fromCol))
				return false;
	}

	// Ô nguồn cùng cột với ô đích
	if (fromCol > toCol) 
	{
		if (fromRow > toRow) 
		{
			for (int i = fromRow - 1; i > toRow; i--) 
				for (int j = fromCol - 1; j > toCol; j--) 
				{
					if ((fromRow - i) == (fromCol - j))
						if (board[i][j] != NULL) // Giữa ô nguồn và ô đích có quân cờ
							return false;
				}
		}
		if (fromRow < toRow) 
		{
			for (int i = fromRow + 1; i < toRow; i++) 
				for (int j = fromCol - 1; j > toCol; j--)
				{
					if ((i - fromRow) == (fromCol - j))
						if (board[i][j] != NULL) // Giữa ô nguồn và ô đích có quân cờ
							return false;
				}
		}
		return true;
	}

	// Ô nguồn cùng hàng với ô đích
	if (fromCol < toCol) 
	{
		if (fromRow > toRow) {
			for (int i = fromRow - 1; i > toRow; i--)
				for (int j = fromCol + 1; j < toCol; j++)
				{
					if ((fromRow - i) == (j - fromCol))
						if (board[i][j] != NULL) // Giữa ô nguồn và ô đích có quân cờ
							return false;
				}
		}
		if (fromRow < toRow) 
		{

			for (int i = fromRow + 1; i < toRow; i++)
				for (int j = fromCol + 1; j < toCol; j++)
				{
					if ((i - fromRow) == (j - fromCol))
						if (board[i][j] != NULL) // Giữa ô nguồn và ô đích có quân cờ
							return false;
				}
		}
		return true;
	}
	return false;
}
