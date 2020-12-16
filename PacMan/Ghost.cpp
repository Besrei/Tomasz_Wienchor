#include "Ghost.h"



Ghost::Ghost()
{
	vp.push_back(eDirection::UP);
	vp.push_back(eDirection::DOWN);
	vp.push_back(eDirection::LEFT);
	vp.push_back(eDirection::RIGHT);
}


Ghost::~Ghost()
{
	delete field;
}

void Ghost::SetDirection(eDirection dir)
{
	direction = dir;
}

void Ghost::SetPosition(sPosition pos)
{
	position = pos;
}

eDirection Ghost::GetDirection()
{
	return direction;
}

sPosition Ghost::GetPosition()
{
	return position;
}