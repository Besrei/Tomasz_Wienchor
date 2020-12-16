#pragma once
#include "Types.h"
class Player
{
private:
	sPosition playerPos;
	eDirection playerDir;

public:
	sPosition GetPlayerPos();
	eDirection GetPlayerDir();
	// Ustawia kierunek ruchu gracza
	void SetPlayerDirection(eDirection);
	void SetPlayerPosition(sPosition);
	Player(int, int);
	~Player();
};

