#include "Queen.h"


Queen::Queen() {
	this->type = 'Q';
	this->numOfMoves = 0;
}
Queen::Queen(char color) {
	this->type = 'Q';
	this->numOfMoves = 0;
	this->color = color;
}
Queen::Queen(char color, Pos pos) {
	this->type = 'Q';
	this->numOfMoves = 0;
	this->color = color;
	this->pos = pos;
	if (color == 'w')
		this->texture.loadFromFile("img/queen_w.png");
	else
		this->texture.loadFromFile("img/queen_b.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->pos.getCoord());
}

// Hàm kiểm tra việc di chuyển đến vị trí đích có hợp lệ hay không
bool Queen::validateMove(Piece*** board, Pos moveToPos) {
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


	//XE
	// Ô nguồn cùng cột với ô đích
	if (fromCol == toCol) {
		if (fromRow > toRow) {
			for (int i = fromRow - 1; i > toRow; i--) {
				if (board[i][fromCol] != NULL) // Giữa ô nguồn và ô đích có quân cờ
					return false;
			}
		}
		if (fromRow < toRow) {
			for (int i = fromRow + 1; i < toRow; i++) {
				if (board[i][fromCol] != NULL) // Giữa ô nguồn và ô đích có quân cờ
					return false;
			}
		}
		return true;
	}

	// Ô nguồn cùng hàng với ô đích
	if (fromRow == toRow) {
		if (fromCol > toCol) {
			for (int i = fromCol - 1; i > toCol; i--) {
				if (board[fromRow][i] != NULL) // Giữa ô nguồn và ô đích có quân cờ
					return false;
			}
		}
		if (fromCol < toCol) {
			for (int i = fromCol + 1; i < toCol; i++) {
				if (board[fromRow][i] != NULL) // Giữa ô nguồn và ô đích có quân cờ
					return false;
			}
		}
		return true;
	}


	//Tượng
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

