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
	// Szeroko�� mapy
	int w;
	// Wysoko�� mapy
	int h;
	std::vector<Ghost*> ghost;
	// Liczba pkt jakie osi�gn� gracz
	unsigned int pkt;
	// Czy gra si� sko�czy�a
	bool endGame;
	// Cz�stotliwo�� od�wierzania mechaniki gry
	int hz = 5;
	// Aktualizuje mechanike gry (poruszanie graczem, wrogami, itp)
	void Update();
	// Zwraca informacj� czy gracz jest w trybie �apania przeciwnik�w
	bool IsBonusActive();
	// Wyryfikacja warunk�w zako�czenia gry
	void CheckIsEndGame();
	Player* pl;
private:
	// Lokacja gdzie maj� spawnowa� si� wrogowie po ich zabiciu
	sPosition m_spawnPoint;
	
	// Porusza graczem o kolejny krok (o ile mo�liwe)
	void MovePlayer(sPosition p);
	// Porusza wrogami
	void MoveGhost();
	void Collision(Ghost *gnemy);
	// Czas jaki pozosta� do ko�ca aktywno�ci bonusu
	int m_bonusActiveTime = 0;
};

