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
	// Na pozycji znajduje siê moneta
	COIN,
	// Na pozycji znajduje siê bonus powoduj¹cy zmiane trybu gry -> ³¹panie wrogów
	COIN2,
	// Na pozycji znajduje siê œciana
	WALL
};
