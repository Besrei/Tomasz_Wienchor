#pragma once
#include "Types.h"

class MapField
{
public:

	MapField();
	~MapField();

	// Stan pozycji na mapie
	eState state;
	// Wartoœæ "zapachu" na jego podstawie poruszaj¹ siê wrogowie
	unsigned int distance = 0;


};

