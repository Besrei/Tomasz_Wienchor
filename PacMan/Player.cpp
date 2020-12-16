#include "Player.h"



Player::Player(int w, int h)
{
	playerPos.x = w;
	playerPos.y = h;
}


Player::~Player()
{
}



sPosition Player::GetPlayerPos()
{
	return playerPos;
}

eDirection Player::GetPlayerDir()
{
	return playerDir;
}

void Player::SetPlayerDirection(eDirection playDir)
{
	playerDir = playDir;
}

void Player::SetPlayerPosition(sPosition playPos)
{
	playerPos = playPos;
}