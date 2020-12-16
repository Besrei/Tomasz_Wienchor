#pragma once
#include "Types.h"
#include "MapField.h"
#include <vector>
class GameMech
{
public:
	// Kolekcja przechowuj�ca wszystkie fragm�ty mapy
	std::vector<MapField> m_map;
	// Oblicza now� pozycj� na mapie na podstawie punktu i kierunku
	sPosition CalcPosition(sPosition, eDirection);
	// Zwraca informacj� o danym fragm�cie mapy
	MapField* Get(sPosition);
	MapField* Get(int x, int y);
	// Weryfikuje czy zadany punkt mie�ci si� w mapie i jest mo�liwy ruch na ten punkt
	bool IsInMap(sPosition);
	GameMech();
	~GameMech();
};

