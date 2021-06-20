#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"

// Class này thể hiện bàn cờ
class Board
{
private:
	Piece*** board; // Mảng 8x8 các con trỏ Piece thể hiện bàn cờ
	char turn; // Lượt đi của màu nào ('w' hoặc 'b')
	int numOfMovesToDraw; // Số nước đi liên tiếp không bắt quân (dẫn đến hoà)

	bool isClick;
	sf::Vector2f mouseClickPos;
	Pos posFrom;
	int squareCanMove[8][8];
	void initSquareCanMove();
	void setSquareCanMove();
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Texture textureHighlight;
	sf::Sprite spriteHighlight;

	sf::Texture texturePromoteW;
	sf::Sprite spritePromoteW;

	sf::Texture texturePromoteB;
	sf::Sprite spritePromoteB;

	Pos posPromote;

	sf::Texture textureEndGame;
	sf::Sprite spriteEndGame;
	sf::Texture textureDraw;
	sf::Sprite spriteDraw;
	sf::Texture textureWhiteWin;
	sf::Sprite spriteWhiteWin;
	sf::Texture textureBlackWin;
	sf::Sprite spriteBlackWin;
	int isEndGame; // 1: chieu het, 2: hoa
	bool isQuit;
	bool isReplay;
public:
	Board();
	~Board();
	void move(Pos moveFromPos, Pos moveToPos); // Di chuyển quân cờ từ ô nguồn đến ô đích
	void play(); // Chọn quân, xuất nước đi, di chuyển
	void draw(); // Vẽ bàn cờ
	bool isControlled(Pos pos); // Kiểm tra ô có bị kiểm soát bởi quân khác màu hay không
	bool isChecked(); // Kiểm tra người chơi có lượt đi đang bị chiếu hay không
	bool isCastlingShort(Pos posFrom); // Kiểm tra nhập thành ngắn
	bool isCastlingLong(Pos posFrom); // Kiểm tra nhập thành dài
	Piece*** getBoard();
	bool isCheckmated(); // Kiểm tra người chơi có lượt đi đang bị chiếu hết hay không
	bool isDraw(); // Kiem tra hoa co
	// fsml
	void update();
	void promoteRender(sf::RenderTarget* target);
	void promoteUpdate(Pos posClick);

	bool cantMove();
	void endGameRender(sf::RenderTarget* target);
	void endGameUpdate(sf::Vector2f pos);
	void setIsEndGame();
	void setPosPromote(Pos pos);
	void render(sf::RenderTarget* target);
	void setMouseClickPos(float, float);
	void setIsClick(bool);

	bool getIsQuit();
	bool getIsReplay();
};

