#pragma once
#include "Types.h"
#include "MapField.h"
#include "Ghost.h"
#include "Player.h"
#include "GameMech.h"
#include <vector>
#include <fstream>
#include <iostream>
class Map: public GameMech
{
public:

	Map();
	~Map();
	// Szerokoœæ mapy
	int w;
	// Wysokoœæ mapy
	int h;
	std::vector<Ghost*> ghost;
	// Liczba pkt jakie osi¹gn¹ gracz
	unsigned int pkt;
	// Czy gra siê skoñczy³a
	bool endGame;
	// Czêstotliwoœæ odœwierzania mechaniki gry
	int hz = 5;
	// Aktualizuje mechanike gry (poruszanie graczem, wrogami, itp)
	void Update();
	// Zwraca informacjê czy gracz jest w trybie ³apania przeciwników
	bool IsBonusActive();
	// Wyryfikacja warunków zakoñczenia gry
	void CheckIsEndGame();
	Player* pl;
private:
	// Lokacja gdzie maj¹ spawnowaæ siê wrogowie po ich zabiciu
	sPosition m_spawnPoint;
	
	// Porusza graczem o kolejny krok (o ile mo¿liwe)
	void MovePlayer(sPosition p);
	// Porusza wrogami
	void MoveGhost();
	void Collision(Ghost *gnemy);
	// Czas jaki pozosta³ do koñca aktywnoœci bonusu
	int m_bonusActiveTime = 0;
};

