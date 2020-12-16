#pragma once
#include "Types.h"
#include "MapField.h"
#include <vector>
class Ghost
{
	eDirection direction;
	sPosition position;
public:
	sPosition p;
	unsigned int bestDistance;
	eDirection temp_direction;
	MapField *field;
	std::vector<eDirection> vp;
	Ghost();
	~Ghost();
	void SetDirection(eDirection);
	void SetPosition(sPosition);
	eDirection GetDirection();
	sPosition GetPosition();
};

