#pragma once
enum eDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct sPosition
{
public:
	sPosition() { x = 0; y = 0; }
	sPosition(int x, int y) { this->x = x; this->y = y; }
	int x;
	int y;
};

enum eState
{
	// Pozycja pusta
	EMPTY,
	// Na pozycji znajduje si� moneta
	COIN,
	// Na pozycji znajduje si� bonus powoduj�cy zmiane trybu gry -> ��panie wrog�w
	COIN2,
	// Na pozycji znajduje si� �ciana
	WALL
};
