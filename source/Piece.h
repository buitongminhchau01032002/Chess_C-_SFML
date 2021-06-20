#pragma once
#include "Pos.h"
#include <SFML/Graphics.hpp>

// Class này thể hiện tổng quát các quân cờ
class Piece
{
protected:
	char type; // Kí hiệu quân cờ
	char color; // Màu quân cờ ('w' hoặc 'b')
	Pos pos; // vị trí quân cờ
	int numOfMoves; // Số lượng nước mà quân cờ đã đi

	sf::Texture texture;
	sf::Sprite sprite;
public:
	char getColor();
	char getType();
	virtual bool validateMove(Piece*** board, Pos moveToPos) = 0; // Kiểm tra di chuyển hợp lệ hay không
	void setPos(Pos pos);
	void addNumOfMoves();
	int getNumOfMoves();
	void setNumOfMoves(int);

	// sfml
	void update();
	void render(sf::RenderTarget* target);
};

