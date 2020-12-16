#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "MapField.h"
#include <Windows.h>
#include <chrono>
class GameWindow
{
public:
	GameWindow();
	~GameWindow();
	void Run();

private:
	sf::RenderWindow *m_window;
	Map m_map;
	void Redraw();
};

