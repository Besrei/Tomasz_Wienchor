#include "GameWindow.h"

GameWindow::GameWindow()
{

}

void GameWindow::Run()
{
	bool blind = false;
	uint64_t lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	uint64_t update = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	m_window = new sf::RenderWindow(sf::VideoMode(m_map.w * 25, m_map.h * 25), "PacMan");

	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window->close();

			// Sterowanie
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == 72 && 
					m_map.IsInMap(m_map.CalcPosition(m_map.pl->GetPlayerPos(), eDirection::RIGHT))) {
					m_map.pl->SetPlayerDirection(eDirection::RIGHT);
				}
				else if (event.key.code == 71 &&
					m_map.IsInMap(m_map.CalcPosition(m_map.pl->GetPlayerPos(), eDirection::LEFT))) {
					m_map.pl->SetPlayerDirection(eDirection::LEFT);
				}
				else if (event.key.code == 73 &&
					m_map.IsInMap(m_map.CalcPosition(m_map.pl->GetPlayerPos(), eDirection::UP))) {
					m_map.pl->SetPlayerDirection(eDirection::UP);
				}
				else if (event.key.code == 74 &&
					m_map.IsInMap(m_map.CalcPosition(m_map.pl->GetPlayerPos(), eDirection::DOWN))) {
					m_map.pl->SetPlayerDirection(eDirection::DOWN);
				}
			}
		}

		m_window->clear();

		update = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		// Aktualizacja silnika gry
		if (!m_map.endGame && lastUpdate + (800 / m_map.hz) < update)
		{
			lastUpdate = update;
			m_map.Update();
		}

		// Wyœwietlenie ekranu koñca gry (miganie ekranem)
		if (m_map.endGame)
		{
			if (lastUpdate + 500 < update)
			{
				blind = !blind;
				lastUpdate = update;
			}
			if (blind)
				Redraw();
			else {
				sf::RectangleShape rect(sf::Vector2f(m_map.w * 25, m_map.h * 25));
				rect.setFillColor(sf::Color::Black);
				m_window->draw(rect);
			}
		}

		else
			Redraw();

		m_window->display();
	}
}

void  GameWindow::Redraw()
{
	// Czyszczenie ekranu
	sf::RectangleShape rect(sf::Vector2f(m_map.w * 25, m_map.h * 25));
	rect.setFillColor(sf::Color::Black);
	m_window->draw(rect);

	// Rysowanie Obszaru mapy
	for (int x = 0; x < m_map.w; x++)
	{
		for (int y = 0; y < m_map.h; y++)
		{
			sf::RectangleShape rect(sf::Vector2f(25, 25));
			rect.setPosition(x * 25, y * 25);
			MapField *field = m_map.Get(x, y);
			switch (field->state)
			{
			case eState::WALL:
				rect.setFillColor(sf::Color::White);
				break;
			case eState::EMPTY:
				rect.setFillColor(sf::Color::Black);
				break;
			case eState::COIN:
				rect.setFillColor(sf::Color::Magenta);
				rect.setSize(sf::Vector2f(2, 2));
				rect.setPosition(x * 25 + 11, y * 25 + 11);
				break;
			case eState::COIN2:
				rect.setFillColor(sf::Color::Magenta);
				rect.setSize(sf::Vector2f(5, 5));
				rect.setPosition(x * 25 + 10, y * 25 + 10);
				break;
			}
			m_window->draw(rect);
		}
	}

	// Rysowanie gracza
	rect = sf::RectangleShape(sf::Vector2f(25, 25));
	rect.setPosition(m_map.pl->GetPlayerPos().x * 25, m_map.pl->GetPlayerPos().y * 25);
	rect.setFillColor(sf::Color::Yellow);
	m_window->draw(rect);

	// Rysowanie wrogów	
	for (auto git : m_map.ghost)
	{
		rect = sf::RectangleShape(sf::Vector2f(25, 25));
		rect.setPosition(git->GetPosition().x * 25, git->GetPosition().y * 25);
		rect.setFillColor(m_map.IsBonusActive() ? sf::Color::Blue : sf::Color::Red);
		m_window->draw(rect);
	}

	// Rysowanie punktów
	sf::String string = sf::String(std::to_string(m_map.pkt).c_str());
	string += sf::String(" pkt");
	m_window->setTitle("PacMan - " + string);
}

GameWindow::~GameWindow()
{
	delete m_window;
}
