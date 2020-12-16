#pragma once
#include "Types.h"
#include "MapField.h"
#include <vector>
class GameMech
{
public:
	// Kolekcja przechowuj¹ca wszystkie fragmêty mapy
	std::vector<MapField> m_map;
	// Oblicza now¹ pozycjê na mapie na podstawie punktu i kierunku
	sPosition CalcPosition(sPosition, eDirection);
	// Zwraca informacjê o danym fragmêcie mapy
	MapField* Get(sPosition);
	MapField* Get(int x, int y);
	// Weryfikuje czy zadany punkt mieœci siê w mapie i jest mo¿liwy ruch na ten punkt
	bool IsInMap(sPosition);
	GameMech();
	~GameMech();
};

