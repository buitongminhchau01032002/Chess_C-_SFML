#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Pos.h"
#include <iostream>
#include <string>
using namespace std;

// Tạo bàn cờ ban đầu
Board::Board() {
	numOfMovesToDraw = 0;
	posPromote = Pos(-1, -1);
	isEndGame = 0;
	isReplay = false;
	turn = 'w';
	isQuit = false;
	board = new Piece**[8];
	for (int i = 0; i < 8; i++) {
		board[i] = new Piece*[8];
		for (int j = 0; j < 8; j++)
			board[i][j] = NULL;
	}

	board[0][4] = new King('w', Pos(0, 4));
	board[7][4] = new King('b', Pos(7, 4));

	board[0][0] = new Rook('w', Pos(0, 0));
	board[0][7] = new Rook('w', Pos(0, 7));
	board[7][0] = new Rook('b', Pos(7, 0));
	board[7][7] = new Rook('b', Pos(7, 7));

	board[0][1] = new Knight('w', Pos(0, 1));
	board[0][6] = new Knight('w', Pos(0, 6));
	board[7][1] = new Knight('b', Pos(7, 1));
	board[7][6] = new Knight('b', Pos(7, 6));

	board[0][2] = new Bishop('w', Pos(0, 2));
	board[0][5] = new Bishop('w', Pos(0, 5));
	board[7][2] = new Bishop('b', Pos(7, 2));
	board[7][5] = new Bishop('b', Pos(7, 5));

	board[0][3] = new Queen('w', Pos(0, 3));
	board[7][3] = new Queen('b', Pos(7, 3));

	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new Pawn('w', Pos(1, i));
		board[6][i] = new Pawn('b', Pos(6, i));
	}
	this->initSquareCanMove();
	this->posFrom = Pos(-1, -1);
	this->isClick = false;

	this->texture.loadFromFile("img/board.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(0.f, 0.f);

	
	this->textureHighlight.loadFromFile("img/squareHighlight.png");
	this->spriteHighlight.setTexture(this->textureHighlight);
	this->spriteHighlight.setPosition(0.f, 0.f);
	

	this->texturePromoteW.loadFromFile("img/promote_w.png");
	this->spritePromoteW.setTexture(this->texturePromoteW);
	this->spritePromoteW.setPosition(0.f, 0.f);

	this->texturePromoteB.loadFromFile("img/promote_b.png");
	this->spritePromoteB.setTexture(this->texturePromoteB);
	this->spritePromoteB.setPosition(0.f, 0.f);

	this->textureEndGame.loadFromFile("img/endgame.png");
	this->spriteEndGame.setTexture(this->textureEndGame);
	this->spriteEndGame.setPosition(0.f, 0.f);

	this->textureWhiteWin.loadFromFile("img/whitewin.png");
	this->spriteWhiteWin.setTexture(this->textureWhiteWin);
	this->spriteWhiteWin.setPosition(0.f, 0.f);

	this->textureBlackWin.loadFromFile("img/blackwin.png");
	this->spriteBlackWin.setTexture(this->textureBlackWin);
	this->spriteBlackWin.setPosition(0.f, 0.f);

	this->textureDraw.loadFromFile("img/draw.png");
	this->spriteDraw.setTexture(this->textureDraw);
	this->spriteDraw.setPosition(0.f, 0.f);

}

Board::~Board() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			delete board[i][j];
	for (int i = 0; i < 8; i++)
		delete[] board[i];
	delete[] board;
}

// Di chuyển quân cờ
// Thay đổi các quân cờ trên board
void Board::move(Pos moveFromPos, Pos moveToPos) {

	// Chèn quân ở ô đích
	if (board[moveToPos.getRow()][moveToPos.getCol()] != NULL)
		delete board[moveToPos.getRow()][moveToPos.getCol()];
	board[moveToPos.getRow()][moveToPos.getCol()] = board[moveFromPos.getRow()][moveFromPos.getCol()];
	board[moveToPos.getRow()][moveToPos.getCol()]->setPos(moveToPos);
	board[moveToPos.getRow()][moveToPos.getCol()]->addNumOfMoves();


	// Xoá quân ở ô nguồn
	board[moveFromPos.getRow()][moveFromPos.getCol()] = NULL;

	// Di chuyển xe nếu nước đi là nhập thành
	if (board[moveToPos.getRow()][moveToPos.getCol()]->getType() == 'K' && moveFromPos.getCol() == 4) {
		if (moveToPos.getCol() == 6) { // Nhập thành ngắn
			board[moveToPos.getRow()][5] = board[moveFromPos.getRow()][7];
			board[moveToPos.getRow()][5]->setPos(Pos(moveToPos.getRow(), 5));
			board[moveToPos.getRow()][5]->addNumOfMoves();
			board[moveFromPos.getRow()][7] = NULL;
		}
		if (moveToPos.getCol() == 2) { // Nhập thành dài
			board[moveToPos.getRow()][3] = board[moveFromPos.getRow()][0];
			board[moveToPos.getRow()][3]->setPos(Pos(moveToPos.getRow(), 3));
			board[moveToPos.getRow()][3]->addNumOfMoves();
			board[moveFromPos.getRow()][0] = NULL;
		}
	}
}

bool Board::isControlled(Pos pos) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board[i][j] != NULL)
				if (turn != board[i][j]->getColor())
					if (board[i][j]->validateMove(board, pos))
						return true;
	return false;
}

bool Board::isChecked() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board[i][j] != NULL)
				if (turn == board[i][j]->getColor())
					if (board[i][j]->getType() == 'K')
						if (this->isControlled(Pos(i, j)))
							return true;
						else
							return false;
}

Piece*** Board::getBoard() {
	Piece*** t;
	t = new Piece**[8];
	for (int i = 0; i < 8; i++) {
		t[i] = new Piece*[8];
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == NULL)
				t[i][j] = NULL;
			else {
				if (board[i][j]->getType() == 'K')
					t[i][j] = new King(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'R')
					t[i][j] = new Rook(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'Q')
					t[i][j] = new Queen(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'N')
					t[i][j] = new Knight(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'B')
					t[i][j] = new Bishop(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'P')
					t[i][j] = new Pawn(board[i][j]->getColor(), Pos(i, j));
				t[i][j]->setNumOfMoves(board[i][j]->getNumOfMoves());
			}
		}
	}
	return t;
}


bool Board::isCastlingShort(Pos posFrom) {
	if (turn == 'w' && posFrom==Pos(0, 4) && board[0][4]!=NULL && board[0][7]!=NULL)
		if (board[0][4]->getType()=='K' && 
			board[0][7]->getType()=='R' &&
			board[0][4]->getNumOfMoves()==0 && 
			board[0][7]->getNumOfMoves()==0 &&
			board[0][5] == NULL &&
			board[0][6] == NULL &&
			!this->isControlled(Pos(0, 4)) &&
			!this->isControlled(Pos(0, 5)) &&
			!this->isControlled(Pos(0, 6))
			)
			return true;
	if (turn == 'b' && posFrom==Pos(7, 4) && board[7][4]!=NULL && board[7][7]!=NULL)
		if (board[7][4]->getType()=='K' && 
			board[7][7]->getType()=='R' &&
			board[7][4]->getNumOfMoves()==0 && 
			board[7][7]->getNumOfMoves()==0 &&
			board[7][5] == NULL &&
			board[7][6] == NULL &&
			!this->isControlled(Pos(7, 4)) &&
			!this->isControlled(Pos(7, 5)) &&
			!this->isControlled(Pos(7, 6))
			)
			return true;
	return false;
}
bool Board::isCastlingLong(Pos posFrom) {
	if (turn == 'w' && posFrom==Pos(0, 4) && board[0][4]!=NULL && board[0][0]!=NULL)
		if (board[0][4]->getType()=='K' && 
			board[0][0]->getType()=='R' &&
			board[0][4]->getNumOfMoves()==0 && 
			board[0][0]->getNumOfMoves()==0 &&
			board[0][1] == NULL &&
			board[0][2] == NULL &&
			board[0][3] == NULL &&
			!this->isControlled(Pos(0, 1)) &&
			!this->isControlled(Pos(0, 2)) &&
			!this->isControlled(Pos(0, 3)) &&
			!this->isControlled(Pos(0, 4))
			)
			return true;
	if (turn == 'b' && posFrom==Pos(7, 4) && board[7][4]!=NULL && board[7][0]!=NULL)
		if (board[7][4]->getType()=='K' && 
			board[7][0]->getType()=='R' &&
			board[7][4]->getNumOfMoves()==0 && 
			board[7][0]->getNumOfMoves()==0 &&
			board[7][1] == NULL &&
			board[7][2] == NULL &&
			board[7][3] == NULL &&
			!this->isControlled(Pos(7, 1)) &&
			!this->isControlled(Pos(7, 2)) &&
			!this->isControlled(Pos(7, 3)) &&
			!this->isControlled(Pos(7, 4))
			)
			return true;
	return false;
}

void Board::update() {

	if (isEndGame != 0) {
		this->endGameUpdate(this->mouseClickPos);
		return;
	}

	if (isClick == true) {
		Pos posClick = Pos::coordToPos(this->mouseClickPos);
		if (!(posPromote == Pos(-1, -1))) {
			this->promoteUpdate(posClick);
			this->setIsEndGame();
			return;
		}
		
		if (this->squareCanMove[posClick.getRow()][posClick.getCol()] == 1) {
			if (board[posClick.getRow()][posClick.getCol()] == NULL) // Kiểm tra có bắt quân hay không
				numOfMovesToDraw++;
			else
				numOfMovesToDraw = 0;
			this->move(posFrom, posClick);
			if (this->turn == 'w')
				turn = 'b';
			else
				turn = 'w';
			this->setIsEndGame();
			setPosPromote(posClick);
			posFrom = Pos(-1, -1);
			this->initSquareCanMove();
			
			
		} else {
			this->initSquareCanMove();
			if (board[posClick.getRow()][posClick.getCol()] != NULL)
				if (board[posClick.getRow()][posClick.getCol()]->getColor() == turn) {
					posFrom = posClick;
					setSquareCanMove();
				} else
					posFrom = Pos(-1, -1);
			else
				posFrom = Pos(-1, -1);
		}
	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board[i][j] != NULL)
				board[i][j]->update();
}
void Board::render(sf::RenderTarget* target) {
	target->draw(this->sprite);
	if (!(posFrom==Pos(-1, -1))) {
		this->spriteHighlight.setPosition(posFrom.getCoord());
		target->draw(spriteHighlight);
	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (squareCanMove[i][j] == 1) {
				this->spriteHighlight.setPosition(Pos(i, j).getCoord());
				target->draw(spriteHighlight);
			}
		}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != NULL)
				board[i][j]->render(target);
		}

	this->promoteRender(target);
	this->endGameRender(target);

}

void Board::initSquareCanMove() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			squareCanMove[i][j] = 0;
}

void Board::setMouseClickPos(float x, float y) {
	this->mouseClickPos.x = x;
	this->mouseClickPos.y = y;
}

void Board::setIsClick(bool cl) {
	this->isClick = cl;
}

void Board::setSquareCanMove() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Pos posTo = Pos(i, j);
			if (board[posFrom.getRow()][posFrom.getCol()]->validateMove(this->board, posTo) == true) {
				// Di chuyển thử
				Piece*** t = this->getBoard(); // t copy lại board
				this->move(posFrom, posTo);

				if (!this->isChecked()) { // Hợp lệ (không bị chiếu)
					this->squareCanMove[i][j] = 1;
				}
				// Giải phóng board, gán lại giá trị ở t
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++)
						delete board[i][j];
				}
				for (int i = 0; i < 8; i++)
					delete[] board[i];
				delete[] board;
				board = t;
			}
			else
				this->squareCanMove[i][j] = 0;
		}
	}
	// Kiểm tra nhập thành ngắn
	if (this->isCastlingShort(posFrom)) {
		this->squareCanMove[posFrom.getRow()][6] = 1;
	}
	// Kiểm tra nhập thành dài
	if (this->isCastlingLong(posFrom)) {
		this->squareCanMove[posFrom.getRow()][2] = 1;
	}
}

bool Board::isCheckmated() {
	if (!this->isChecked())
		return false;
	for (int fromRow = 0; fromRow < 8; fromRow++)
		for (int fromCol = 0; fromCol < 8; fromCol++)
			if (board[fromRow][fromCol] != NULL)
				if (board[fromRow][fromCol]->getColor() == turn)
					for (int toRow = 0; toRow < 8; toRow++)
						for (int toCol = 0; toCol < 8; toCol++)
							if (board[fromRow][fromCol]->validateMove(board, Pos(toRow, toCol)) == true) {
								bool isReturnFalse = false;
								// Di chuyển thử
								Piece*** t = this->getBoard(); // t copy lại board
								this->move(Pos(fromRow, fromCol), Pos(toRow, toCol));
								if (!this->isChecked()) { // Hợp lệ (không bị chiếu)
									isReturnFalse = true;
								}
								// Giải phóng board, gán lại giá trị ở t
								for (int i = 0; i < 8; i++) {
									for (int j = 0; j < 8; j++)
										delete board[i][j];
								}
								for (int i = 0; i < 8; i++)
									delete[] board[i];
								delete[] board;
								board = t;

								if (isReturnFalse)
									return false;
							}
							return true;
}


bool Board::isDraw() {
	// Hoà khi đi đủ 50 nước không bắt quân
	if (numOfMovesToDraw == 50)
		return true;

	// Hoà khi không đủ lực lượng chiếu hết
	// vua và vua+tượng, vua và vua+mã
	int Nw = 0;
	int Nb = 0;
	int Bw = 0;
	int Bb = 0;
	bool isBreak;
	for (int i = 0; i < 8; i++) {
		isBreak = false;
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != NULL) {
				// Xuất hiện quân khác ngoài Mã, Tượng, Vua
				if (board[i][j]->getType() != 'N' && board[i][j]->getType() != 'B' && board[i][j]->getType() != 'K')
					isBreak = true;
				// Cộng thêm các quân là mã, tượng
				if (board[i][j]->getType() == 'N' && board[i][j]->getColor() == 'w')
					Nw++;
				if (board[i][j]->getType() == 'N' && board[i][j]->getColor() == 'b')
					Nb++;
				if (board[i][j]->getType() == 'B' && board[i][j]->getColor() == 'w')
					Bw++;
				if (board[i][j]->getType() == 'B' && board[i][j]->getColor() == 'b')
					Bb++;

				if (Nw+Bw == 2 || Nb+Bb == 2)
					isBreak = true;
			}
			if (isBreak)
				break;
		}
		if (isBreak)
			break;
	}
	if (Nw+Bw <= 1 && Nb+Bb <= 1 && !isBreak)
		return true;

	// Hoà do hết nước đi, vua không bị chiếu
	if (!this->isChecked()) {
		for (int fromRow = 0; fromRow < 8; fromRow++)
			for (int fromCol = 0; fromCol < 8; fromCol++)
				if (board[fromRow][fromCol] != NULL)
					if (board[fromRow][fromCol]->getColor() == turn)
						for (int toRow = 0; toRow < 8; toRow++)
							for (int toCol = 0; toCol < 8; toCol++)
								if (board[fromRow][fromCol]->validateMove(board, Pos(toRow, toCol)) == true) {
									bool isReturnFalse = false;
									// Di chuyển thử
									Piece*** t = this->getBoard(); // t copy lại board
									this->move(Pos(fromRow, fromCol), Pos(toRow, toCol));
									if (!this->isChecked()) { // Hợp lệ (không bị chiếu)
										isReturnFalse = true;
									}
									// Giải phóng board, gán lại giá trị ở t
									for (int i = 0; i < 8; i++) {
										for (int j = 0; j < 8; j++)
											delete board[i][j];
									}
									for (int i = 0; i < 8; i++)
										delete[] board[i];
									delete[] board;
									board = t;

									if (isReturnFalse)
										return false;
								}
								return true;
	} else
		return false;
}

void Board::promoteRender(sf::RenderTarget* target) {
	if (!(posPromote == Pos(-1, -1))) {
		if (posPromote.getRow() == 7) {
			target->draw(this->spritePromoteW);
		} else if (posPromote.getRow() == 0) {
			target->draw(this->spritePromoteB);
		}
	}
}
void Board::promoteUpdate(Pos posClick) {
	if (posClick == Pos(4, 3)) {
		delete board[posPromote.getRow()][posPromote.getCol()];
		board[posPromote.getRow()][posPromote.getCol()] = new Queen(turn, Pos(posPromote.getRow(),posPromote.getCol()));
		posPromote = Pos(-1, -1);
		if (this->turn == 'w')
			turn = 'b';
		else
			turn = 'w';
	} else if (posClick == Pos(4, 4)) {
		delete board[posPromote.getRow()][posPromote.getCol()];
		board[posPromote.getRow()][posPromote.getCol()] = new Rook(turn, Pos(posPromote.getRow(),posPromote.getCol()));
		posPromote = Pos(-1, -1);
		if (this->turn == 'w')
			turn = 'b';
		else
			turn = 'w';
	} else if (posClick == Pos(3, 3)) {
		delete board[posPromote.getRow()][posPromote.getCol()];
		board[posPromote.getRow()][posPromote.getCol()] = new Knight(turn, Pos(posPromote.getRow(),posPromote.getCol()));
		posPromote = Pos(-1, -1);
		if (this->turn == 'w')
			turn = 'b';
		else
			turn = 'w';
	} else if (posClick == Pos(3, 4)) {
		delete board[posPromote.getRow()][posPromote.getCol()];
		board[posPromote.getRow()][posPromote.getCol()] = new Bishop(turn, Pos(posPromote.getRow(),posPromote.getCol()));
		posPromote = Pos(-1, -1);
		if (this->turn == 'w')
			turn = 'b';
		else
			turn = 'w';
	}
}
void Board::setPosPromote(Pos pos) {
	if (board[pos.getRow()][pos.getCol()]->getType() == 'P' && (pos.getRow() == 0 || pos.getRow() == 7)) {
		posPromote = pos;
		if (this->turn == 'w')
			turn = 'b';
		else
			turn = 'w';
	} else
		posPromote = Pos(-1, -1);

}

void Board::setIsEndGame() {
	bool isChecked_ = false;
	if (this->isChecked())
		isChecked_ = true;

	bool cantMove_ = false;
	if (this->cantMove())
		cantMove_ = true;
	if (isChecked_ && cantMove_) {
		isEndGame = 1;
		return;
	}
	if (!isChecked_ && cantMove_) {
		isEndGame = 2;
		return;
	}
	// Hoà khi đi đủ 50 nước không bắt quân
	if (numOfMovesToDraw == 50) {
		isEndGame = 2;
		return;
	}
	// Hoà khi không đủ lực lượng chiếu hết
	// vua và vua+tượng, vua và vua+mã
	int Nw = 0;
	int Nb = 0;
	int Bw = 0;
	int Bb = 0;
	bool isBreak;
	for (int i = 0; i < 8; i++) {
		isBreak = false;
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != NULL) {
				// Xuất hiện quân khác ngoài Mã, Tượng, Vua
				if (board[i][j]->getType() != 'N' && board[i][j]->getType() != 'B' && board[i][j]->getType() != 'K')
					isBreak = true;
				// Cộng thêm các quân là mã, tượng
				if (board[i][j]->getType() == 'N' && board[i][j]->getColor() == 'w')
					Nw++;
				if (board[i][j]->getType() == 'N' && board[i][j]->getColor() == 'b')
					Nb++;
				if (board[i][j]->getType() == 'B' && board[i][j]->getColor() == 'w')
					Bw++;
				if (board[i][j]->getType() == 'B' && board[i][j]->getColor() == 'b')
					Bb++;

				if (Nw+Bw == 2 || Nb+Bb == 2)
					isBreak = true;
			}
			if (isBreak)
				break;
		}
		if (isBreak)
			break;
	}
	if (Nw+Bw <= 1 && Nb+Bb <= 1 && !isBreak) {
		isEndGame = 2;
		return;
	}
	isEndGame = 0;
	
}

bool Board::cantMove() {
	for (int fromRow = 0; fromRow < 8; fromRow++)
		for (int fromCol = 0; fromCol < 8; fromCol++)
			if (board[fromRow][fromCol] != NULL)
				if (board[fromRow][fromCol]->getColor() == turn)
					for (int toRow = 0; toRow < 8; toRow++)
						for (int toCol = 0; toCol < 8; toCol++)
							if (board[fromRow][fromCol]->validateMove(board, Pos(toRow, toCol)) == true) {
								bool isReturnFalse = false;
								// Di chuyển thử
								Piece*** t = this->getBoard(); // t copy lại board
								this->move(Pos(fromRow, fromCol), Pos(toRow, toCol));
								if (!this->isChecked()) { // Hợp lệ (không bị chiếu)
									isReturnFalse = true;
								}
								// Giải phóng board, gán lại giá trị ở t
								for (int i = 0; i < 8; i++) {
									for (int j = 0; j < 8; j++)
										delete board[i][j];
								}
								for (int i = 0; i < 8; i++)
									delete[] board[i];
								delete[] board;
								board = t;

								if (isReturnFalse)
									return false;
							}
							return true;
}

void Board::endGameUpdate(sf::Vector2f pos) {
	if (pos.x >= 100 && pos.x <= 300 && pos.y >= 200 && pos.y <= 275)
		isReplay = true;
	if (pos.x >= 100 && pos.x <= 300 && pos.y >= 300 && pos.y <= 375)
		isQuit = true;
}

void Board::endGameRender(sf::RenderTarget* target) {
	if (isEndGame != 0) {
		target->draw(this->spriteEndGame);
		if (isEndGame == 2) {
			target->draw(this->spriteDraw);
		} else if (isEndGame == 1)
			if (turn == 'w')
				target->draw(this->spriteBlackWin);
			else
				target->draw(this->spriteWhiteWin);
	}
}

bool Board::getIsReplay() {return isReplay;}
bool Board::getIsQuit() {return isQuit;}