#include "GameMech.h"



GameMech::GameMech()
{
}


GameMech::~GameMech()
{
}

sPosition GameMech::CalcPosition(sPosition position, eDirection direction)
{
	switch (direction) {
	case eDirection::UP:
		return sPosition(position.x, position.y - 1);
	case eDirection::DOWN:
		return sPosition(position.x, position.y + 1);
	case eDirection::LEFT:
		return sPosition(position.x - 1, position.y);
	case eDirection::RIGHT:
		return sPosition(position.x + 1, position.y);
	}
}

MapField* GameMech::Get(sPosition p)
{
	return Get(p.x, p.y);
}


MapField* GameMech::Get(int x, int y)
{
	return &m_map.at(y*28 + x);
}

bool GameMech::IsInMap(sPosition p)
{
	if (p.x < 0 || p.y < 0 || p.x >= 28 || p.y >= 31 )
		return false;
	if (Get(p)->state == eState::WALL)
		return false;
	return true;
}