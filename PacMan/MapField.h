#pragma once
#include "Types.h"

class MapField
{
public:

	MapField();
	~MapField();

	// Stan pozycji na mapie
	eState state;
	// Warto�� "zapachu" na jego podstawie poruszaj� si� wrogowie
	unsigned int distance = 0;


};

