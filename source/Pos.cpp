#include "Pos.h"
#include <iostream>
#include <string>
using namespace std;

Pos::Pos() {
	row = 0;
	col = 0;
}

Pos::Pos(int r, int c) {
	row = r;
	col = c;
}

int Pos::getRow() {
	return row;
}
int Pos::getCol() {
	return col;
}

bool Pos::operator==(const Pos& posOther) {
	if (col == posOther.col && row == posOther.row)
		return true;
	return false;
}

Pos Pos::toPos(std::string s) {
	int row = -1;
	int col = -1;
	if (s[0] == 'a')
		col = 0;
	else if (s[0] == 'b')
		col = 1;
	else if (s[0] == 'c')
		col = 2;
	else if (s[0] == 'd')
		col = 3;
	else if (s[0] == 'e')
		col = 4;
	else if (s[0] == 'f')
		col = 5;
	else if (s[0] == 'g')
		col = 6;
	else if (s[0] == 'h')
		col = 7;

	if (s[1] == '1')
		row = 0;
	else if (s[1] == '2')
		row = 1;
	else if (s[1] == '3')
		row = 2;
	else if (s[1] == '4')
		row = 3;
	else if (s[1] == '5')
		row = 4;
	else if (s[1] == '6')
		row = 5;
	else if (s[1] == '7')
		row = 6;
	else if (s[1] == '8')
		row = 7;
	if (row == -1 || col == -1) {
		row = -1;
		col = -1;
	}
	return Pos(row, col);
}

string Pos::toString() {
	string t = "a1";
	if (col == 0)
		t[0] = 'a';
	else if (col == 1)
		t[0] = 'b';
	else if (col == 2)
		t[0] = 'c';
	else if (col == 3)
		t[0] = 'd';
	else if (col == 4)
		t[0] = 'e';
	else if (col == 5)
		t[0] = 'f';
	else if (col == 6)
		t[0] = 'g';
	else if (col == 7)
		t[0] = 'h';

	if (row == 0)
		t[1] = '1';
	else if (row == 1)
		t[1] = '2';
	else if (row == 2)
		t[1] = '3';
	else if (row == 3)
		t[1] = '4';
	else if (row == 4)
		t[1] = '5';
	else if (row == 5)
		t[1] = '6';
	else if (row == 6)
		t[1] = '7';
	else if (row == 7)
		t[1] = '8';
	return t;
}

void Pos::intput() {
	string t;
	getline(cin, t);
	*this = Pos::toPos(t);
}

void Pos::output() {
	cout << this->toString();
}

sf::Vector2f Pos::getCoord() {
	sf::Vector2f t;
	t.x = col*SQUARE_SIZE;
	t.y = WINDOW_WIDTH-(row+1)*SQUARE_SIZE;
	return t;
}

Pos Pos::coordToPos(sf::Vector2f coord) {
	Pos t;
	t.col = int(coord.x) / SQUARE_SIZE;
	t.row = 8 - (int(coord.y) / SQUARE_SIZE)-1;
	if (t.col < 0 || t.col >= 8 || t.row < 0 || t.row >= 8)
		t = Pos(-1, -1);
	return t;
}