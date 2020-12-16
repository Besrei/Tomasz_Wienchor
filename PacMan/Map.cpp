#include "Map.h"



Map::Map()
{
	char c;
	h = 0;
	w = 0;
	endGame = false;
	pkt = 0;

	// Wczytanie mapy
	std::ifstream file;
	file.open("map.txt");
	if (!file.good())
	{
		throw "nie mozna otworzyæ pliku z map¹, proszê za³adowaæ go ponownie";
		exit(1);
	}
	while (!file.eof())
	{
		file.read(&c, 1);

		// Wróg
		if (c == 'E')
		{
			Ghost *en = new Ghost();
			en->SetDirection(eDirection::RIGHT);
			en->SetPosition({ w,h });
			ghost.push_back(en);
			c = ' ';
		}
		// Gracz
		else if (c == 'P')
		{
			pl = new Player(w, h);
			c = ' ';
		}
		// Spawn point
		else if (c == 'S')
		{
			m_spawnPoint.x = w;
			m_spawnPoint.y = h;
			c = '#';
		}

		// Moneta
		if (c == '*') {
			MapField field = MapField();
			field.state = eState::COIN;
			field.distance = 500;
			m_map.push_back(field);
		}
		// Pusta przestrzeñ
		else if (c == ' ') {
			MapField field = MapField();
			field.state = eState::EMPTY;
			field.distance = 500;
			m_map.push_back(field);
		}
		// Œciana
		else if (c == '#') {
			MapField field = MapField();
			field.state = eState::WALL;
			field.distance = 0;
			m_map.push_back(field);
		}
		// Moneta bonusowa
		else if (c == '0') {
			MapField field = MapField();
			field.state = eState::COIN2;
			field.distance = 500;
			m_map.push_back(field);
		}
		w++;
		if (c == '\n')
		{
			++h;
			w = 0;
		}
	}
	--w;
	file.close();

	// Wytyczenie kierunku ruchu gracza
	if (IsInMap(CalcPosition(pl->GetPlayerPos(), eDirection::UP)))
		pl->SetPlayerDirection(eDirection::UP);
	else if (IsInMap(CalcPosition(pl->GetPlayerPos(), eDirection::DOWN)))
		pl->SetPlayerDirection(eDirection::DOWN);
	else if (IsInMap(CalcPosition(pl->GetPlayerPos(), eDirection::LEFT)))
		pl->SetPlayerDirection(eDirection::LEFT);
	else
		pl->SetPlayerDirection(eDirection::RIGHT);
}

void Map::Update() {

	MovePlayer(CalcPosition(pl->GetPlayerPos(), pl->GetPlayerDir()));
	MoveGhost();


	// Aktualizacja zapachu na mapie
	for (int i = 0; i < m_map.size(); i++)
	{
		if (m_map.at(i).distance > 1)
			--m_map.at(i).distance;
	}

	// Aktualizacja czasu bonusu
	if (IsBonusActive())
		--m_bonusActiveTime;
}

void Map::Collision(Ghost *ghost) {
	// Bonus aktywny -> zabicie wroga
	if (IsBonusActive())
	{
		ghost->SetPosition(m_spawnPoint);
		pkt += 50;
	}
	// bonus nieaktywny -> zabicie gracza
	else {
		endGame = true;
	}
}

bool Map::IsBonusActive() {
	return m_bonusActiveTime > 0;
}

void Map::CheckIsEndGame()
{
	// Weryfikacja czy na mapie pozosta³y jakieœ monety
	bool coinExist = false;
	for (auto mit: m_map)
	{
		if (mit.state == eState::COIN ||
			mit.state == eState::COIN2)
		{
			coinExist = true;
			break;
		}
	}
	if (!coinExist)
		endGame = true;
}

void Map::MoveGhost() {
	// Poruszenie wrogami
	
	// Mo¿liwe kierunki
	
	for (auto git :ghost){
		git->bestDistance = 0;
		if (IsBonusActive()) --git->bestDistance;


		git->temp_direction = git->GetDirection();

		// Aktualny kierunek poruszania siê
		git->p = CalcPosition(git->GetPosition(), git->temp_direction);
		if (IsInMap(git->p))
			git->bestDistance = Get(git->p)->distance;

		// Szukanie alternatywnego kierunku (lepszego)
		for (auto vit :git->vp)
		{
			git->p = CalcPosition(git->GetPosition(), vit);
			if (IsInMap(git->p))
			{
				git->field = Get(git->p);
				if (!IsBonusActive() && git->bestDistance < git->field->distance ||
					IsBonusActive() && git->bestDistance > git->field->distance)
				{
					git->bestDistance = git->field->distance;
					git->SetDirection(vit);
				}
			}
		}

		// Poruszenie wrogiem i modyfikacja "zapachu" na mapie
		git->SetPosition(CalcPosition(git->GetPosition(), git->GetDirection()));
		git->field = Get(git->GetPosition());
		if (!IsBonusActive() && git->field->distance > 1)
			--git->field->distance;
		if (IsBonusActive() && git->field->distance < -1)
			++git->field->distance;

		// Detekcja kolizji
		if (git->GetPosition().x == pl->GetPlayerPos().x && git->GetPosition().y == pl->GetPlayerPos().y)
			Collision(git);
	}
}

void Map::MovePlayer(sPosition p)
{
	if (IsInMap(p))
	{
		switch (Get(p)->state)
		{
		case eState::COIN2:
			m_bonusActiveTime = 5 * hz; // Nadanie bonusu
			CheckIsEndGame();
		case eState::COIN:
			pkt += 1;
			CheckIsEndGame();
		case eState::EMPTY:
			pl->SetPlayerPosition(p);
			Get(p)->distance = 1000;
			Get(p)->state = eState::EMPTY;
			CheckIsEndGame();
		}
	}

	// Interakcja z wrogami
	for (auto git: ghost)
	{
		// Zderzenie z wrogiem
		if (git->GetPosition().x == pl->GetPlayerPos().x && git->GetPosition().y == pl->GetPlayerPos().y)
		{
			Collision(git);
		}
	}
}

Map::~Map()
{
	for (int i = 0; i < ghost.size(); i++)
	{
		delete ghost.at(i);
	}
}
