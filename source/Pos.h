#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "constValue.h"
// Class này thể hiện vị trí các quân cơ
class Pos {
private:
	int row;
	int col;
public:
	Pos();
	Pos(int, int);
	void intput(); // Nhập kí hiệu trên bàn cờ
	void output(); // Xuất kí hiệu trên bàn cờ
	int getRow();
	int getCol();
	bool operator==(const Pos& posOther);
	static Pos toPos(std::string); // Chuyển từ kí hiệu trên bàn cờ sang dạng Pos
	std::string toString(); // Chuyển Pos sang kí hiệu
	sf::Vector2f getCoord();
	static Pos coordToPos(sf::Vector2f coord);
};
