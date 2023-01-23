#include "Game.h"
#include "KeyDown.h"

Game::Game() : _isGameActive(false), _hardMode(false), _successfulBkgRead(false),
	_activeLevel(0), _crystalsOnLvl(0), _heartsOnLvl(0), _keysOnLvl(0)
{
	_manager   = new GameManager();
	_settings  = _manager->GetSettings();

	const int renSizeX = _settings->lvlSizeX + _settings->hudMaxSizeX;
	const int renSizeY = _settings->lvlSizeY + _settings->hudMaxSizeY;
	_renSys = new RenderSystem(renSizeY, renSizeX);

	_hero	= new Hero();
	_empty	= new Object(Entity::empty);
	_wall   = new Object(Entity::wall);
	_fog    = new Object(Entity::fogOfWar);

	_objectsMap = new Object** [_settings->lvlSizeY];
	_fogOfWarB  = new bool* [_settings->lvlSizeY];

	for (int y = 0; y < _settings->lvlSizeY; ++y)
	{
		_objectsMap[y] = new Object* [_settings->lvlSizeX];
		_fogOfWarB[y]  = new bool[_settings->lvlSizeX] { false };

		for (int x = 0; x < _settings->lvlSizeX; ++x)
			_objectsMap[y][x] = nullptr;
	}
}

Game::~Game()
{
	ClearObjectMap();
	for (int y = 0; y < _settings->lvlSizeY; ++y)
	{
		delete _objectsMap[y];
		delete _fogOfWarB[y];
	}
	delete[] _objectsMap;
	delete[] _fogOfWarB;

	delete _hero;
	delete _empty;
	delete _wall;
	delete _fog;

	delete _renSys;
	delete _manager;
}

void Game::Start()
{
	ChooseMode();
	SetupSettings();
	_isGameActive = true;

	while (_activeLevel < _manager->GetSettings()->levelsCount)
	{
		Initialize();

		while (_isGameActive)
		{
			Render();
			Move();
		}

		_activeLevel++;
		_isGameActive = true;
	}

	Shutdown();
}

void Game::ChooseMode()
{
	_renSys->SendText(1, 4, "Choose mode (1 - s1mple, 2 - hard)");
	_renSys->Render();

	bool check = true;
	while(check)
	{
		switch (KeyDown::getWaitKey())
		{
			case Key::NUM_1:   check = false;	break;
			case Key::NUM_2:   check = false;	_hardMode = true;	break;

			default:
			_renSys->SendText(2, 4, "Just choose mode -_-", static_cast<Color>(rand() % 15 + 1));	// 15 Colors (without black)
			_renSys->Render();
		}
	}
}

void Game::SetupSettings()
{
	// Setting up the inventory
	_hero->SetItem(Item::heart, _hardMode ? _settings->normalStartHearts : _settings->eazyStartHearts);
}

void Game::ClearObjectMap()
{
	for (int y = 0; y < _settings->lvlSizeY; ++y)
		for (int x = 0; x < _settings->lvlSizeX; ++x)
			if ((_objectsMap[y][x] != _hero) && (_objectsMap[y][x] != _empty) 
				&& (_objectsMap[y][x] != _wall) && (_objectsMap[y][x] != _fog))
			{
				delete _objectsMap[y][x];
				_objectsMap[y][x] = nullptr;
			}
}

Object* Game::CreateObject(unsigned char symbol, Coord coord)
{
	return new Object(symbol, coord);
}

void Game::Shutdown()
{
	_renSys->Clear();
	_renSys->SendText(1, 4, "Thank you for playing :) Bye - bye!");
	_renSys->Render();

	Sleep(3000);
	_renSys->Clear();
	_renSys->Render();
}

void Game::Initialize()
{
	// Set default items value on this level
	SetDefaultItemsValueOnLvl();
	_successfulBkgRead = false;

	// Clear object map
	ClearObjectMap();

	// Load level and objects
	if (!_manager->ReadLevel(_activeLevel))
	{
		_isGameActive = false;
		return;
	}

	const std::string* level(_manager->GetLastLevel());
	for (int y = 0; y < _settings->lvlSizeY; ++y)
		for (int x = 0; x < _settings->lvlSizeX; ++x)
		{
			if (_hardMode)
				_fogOfWarB[y][x] = true;

			// Take symbol from level map
			unsigned char symbol = level->at(y * _settings->lvlSizeX + x);

			// Create an object
			if (symbol == _hero->GetMapSymbol())
			{
				_hero->SetCoord(x, y);

				// Set hero on objects map
				_objectsMap[y][x] = _hero;
			}
			else if (symbol == _empty->GetMapSymbol())
				_objectsMap[y][x] = _empty;	
			else if (symbol == _wall->GetMapSymbol())
				_objectsMap[y][x] = _wall;
			else if (symbol == _fog->GetMapSymbol())
				_objectsMap[y][x] = _fog;
			else
			{
				// Create and set the object on objects map
				Object* object = CreateObject(symbol, Coord{ x,y });
				_objectsMap[y][x] = object;
			}

			switch (_objectsMap[y][x]->GetEntity())
			{
				case Entity::crystal:    _crystalsOnLvl++;    break;
				case Entity::heart:      _heartsOnLvl++;      break;
				case Entity::key:        _keysOnLvl++;        break;
			}
		}

	// Clear render system
	_renSys->Clear();

	// Render Background
	// if a background does not exists, just do not render it
	// if hard mode is false, draw the entire background
	// if hard mode is true, memorizing a successful background read for rendering during fog dispel
	if (_manager->ReadLevel(_activeLevel, true))
		if (!_hardMode)
		{
			const std::string* lvlBkg(_manager->GetLastLevel());
			for (int y = 0; y < _settings->lvlSizeY; ++y)
				for (int x = 0; x < _settings->lvlSizeX; ++x)
					if ((y * _settings->lvlSizeX + x) < lvlBkg->size())
						_renSys->DrawBkgCharColor(y, x, Object::GetInitColorFromBkgMap(lvlBkg->at(y * _settings->lvlSizeX + x)));
		}
		else
			_successfulBkgRead = true;
	
	// Remember the inventory state at the level start
	_inventoryAtLevelStart = _hero->GetInventory();

	// Dispelling the fog of war around the player
	Coord hero_coord = _hero->GetCoord();
	DispelFog(hero_coord.y, hero_coord.x);
}

void Game::Render()
{
	RenderMap();
	RenderHud();
	_renSys->Render();
}

void Game::RenderMap()
{
	for (int y = 0; y < _settings->lvlSizeY; ++y)
		for (int x = 0; x < _settings->lvlSizeX; ++x)
			if (!_fogOfWarB[y][x])
				_renSys->DrawChar(y, x, _objectsMap[y][x]->GetRenderObject());
			else
				_renSys->DrawChar(y, x, _fog->GetRenderObject());
}

void Game::RenderHud()
{
	Inventory inv = _hero->GetInventory();
	static const int x = _settings->lvlSizeX + _settings->hudIndentX; // X indent
	static const int y = _settings->lvlSizeY + 1;                     // Y indent

	SendHudText(2, x, "Level %i  ", _activeLevel + 1);
	SendHudText(4, x, "Level Key", Color::blue);
	inv.lvlKey ? SendHudText(4, x+9, ": yeap", Color::blue) : SendHudText(4, x+9, ": nope");
	
	SendHudText(5, x, "Keys", Color::yellow);
	SendHudText(5, x+4, ": %i  ", inv.keys);
	SendHudText(6, x, "Hearts", Color::red);
	SendHudText(6, x+6, ": %i  ", inv.hearts);
	SendHudText(7, x, "Crystals", Color::darkMagenta);
	SendHudText(7, x+8, ": %i  ", inv.crystals);

	SendHudText(9, x, "Keys", Color::yellow);
	SendHudText(9, x+4, " on level: %i  ", _keysOnLvl);
	SendHudText(10, x, "Hearts", Color::red);
	SendHudText(10, x+6, " on level: %i  ", _heartsOnLvl);
	SendHudText(11, x, "Crystals", Color::darkMagenta);
	SendHudText(11, x+8, " on level: %i  ", _crystalsOnLvl);

	SendHudText(13, x, "Hero X coord: %i  ", _hero->GetCoord().x);
	SendHudText(14, x, "Hero Y coord: %i  ", _hero->GetCoord().y);
	
	SendHudText(16, x, "Objects count: %i  ", Object::GetObjectsCount());
	
	SendHudText(y,   4, "Use WASD to move ");
	SendHudText(y,   4+17, "Hero", Color::green);
	SendHudText(y+1, 4, "Press ? to restart level.");
	SendHudText(y+1, 4+6,  "R", Color::red);
}

void Game::SendHudText(int y, int x, const char* text, Color symbolColor, Color bkgColor)
{
	static char textBuffer[50];

	sprintf_s(textBuffer, text, 50);
	_renSys->SendText(y, x, textBuffer, symbolColor, bkgColor);
}

void Game::SendHudText(int y, int x, const char* text, int count, Color symbolColor, Color bkgColor)
{
	static char textBuffer[50];

	sprintf_s(textBuffer, text, count, 50);
	_renSys->SendText(y, x, textBuffer, symbolColor, bkgColor);
}

void Game::Move()
{
	Coord c = _hero->GetCoord();

	switch (KeyDown::getWaitKey())
	{
		case Key::W: case Key::KEY_UP:      MoveHeroTo(c.y - 1, c.x);   break;
		case Key::S: case Key::KEY_DOWN:    MoveHeroTo(c.y + 1, c.x);   break;
		case Key::A: case Key::KEY_LEFT:    MoveHeroTo(c.y, c.x - 1);   break;
		case Key::D: case Key::KEY_RIGHT:   MoveHeroTo(c.y, c.x + 1);   break;

		case Key::R:   RestartLevel();   break;

		case Key::NUM_1:   _activeLevel--;   Initialize();   break;
		case Key::NUM_2:   _activeLevel++;   Initialize();   break;	
	}
}

void Game::MoveHeroTo(int y, int x)
{
	if (x < 0 || y < 0 || x >= _settings->lvlSizeX || y >= _settings->lvlSizeY)
		return;

	Object* collidingObject = _objectsMap[y][x];
	bool canMove = false;

	switch (collidingObject->GetEntity())
	{
		case Entity::empty:
		{
			canMove = true;
			break;
		}
		case Entity::crystal:
		{
			_hero->AddItem(Item::crystal);
			_crystalsOnLvl--;

			canMove = true;
			break;
		}
		case Entity::heart:
		{
			_hero->AddItem(Item::heart);
			_heartsOnLvl--;

			canMove = true;
			break;
		}
		case Entity::key:
		{
			_hero->AddItem(Item::key);
			_keysOnLvl--;

			canMove = true;
			break;
		}
		case Entity::levelKey:
		{
			_hero->AddItem(Item::lvlKey);

			canMove = true;
			break;
		}
		case Entity::mine:
		{
			RestartLevel();
			break;
		}
		case Entity::exitDoor:
		{
			_isGameActive = false;
			break;
		}
		case Entity::box:
		{
			// Hero move direction
			Coord heroCoord = _hero->GetCoord();
			int heroDirectionY = y - heroCoord.y;
			int heroDirectionX = x - heroCoord.x;

			int objBehindY = y + heroDirectionY;
			int objBehindX = x + heroDirectionX;

			// Check map border
			if (objBehindX < 0 || objBehindX >= _settings->lvlSizeX 
				|| objBehindY < 0 || objBehindY >= _settings->lvlSizeY)
				return;

			// Check space behind the box
			// and handling collisions with objects
			Entity entityBehindBox = _objectsMap[objBehindY][objBehindX]->GetEntity();
			if ((entityBehindBox == Entity::empty)
				|| (entityBehindBox == Entity::crystal)
				|| (entityBehindBox == Entity::heart)
				|| (entityBehindBox == Entity::key)
				|| (entityBehindBox == Entity::levelKey))
			{
				// Bye bye, Object
				if (entityBehindBox != Entity::empty)
				{
					delete _objectsMap[objBehindY][objBehindX];

					switch (entityBehindBox)
					{
						case Entity::crystal:	_crystalsOnLvl--;    break;
						case Entity::heart:		_heartsOnLvl--;		 break;
						case Entity::key:       _keysOnLvl--;        break;
						case Entity::levelKey:  break;
					}
				}

				// Replace box
				Object* boxObject = collidingObject;
				_objectsMap[y][x] = _empty;
				_objectsMap[objBehindY][objBehindX] = boxObject;

				canMove = true;
			}

			// Logic box for Mines
			if (entityBehindBox == Entity::mine)
				RestartLevel();

			break;
		}
		case Entity::door:
		{
			if (_hero->CheckKey())
			{
				_hero->TakeItem(Item::key);

				canMove = true;
				break;
			}
		}
		case Entity::levelDoor:
		{
			if (_hero->CheckLvlkey())
			{
				_hero->TakeItem(Item::lvlKey);

				canMove = true;
				break;
			}
		}
	}

	if (canMove)
	{
		Coord heroCoord = _hero->GetCoord();
		Object* actualObject = _objectsMap[y][x];

		// Remove Hero and set Empty
		_objectsMap[heroCoord.y][heroCoord.x] = _empty;
		if ((actualObject != _hero) && (actualObject != _empty) && (actualObject != _fog))
			delete actualObject;

		// Set Hero on objects map and set his position
		_objectsMap[y][x] = _hero;
		_hero->SetCoord(x, y);

		// Dispel Fog of war
		if (_hardMode)
			DispelFog(y, x);
	}
}

void Game::DispelFog(int y_pos, int x_pos)
{
	if (_hardMode && _successfulBkgRead)
	{
		const std::string* lvlBkg(_manager->GetLastLevel());
		for (int y = y_pos - 2; y <= y_pos + 2; ++y)
			for (int x = x_pos - 3; x <= x_pos + 3; ++x)
				if (x < _settings->lvlSizeX && y < _settings->lvlSizeY && x >= 0 && y >= 0
					&& (_fogOfWarB[y][x] == true))
				{
					if ((y * _settings->lvlSizeX + x) < lvlBkg->size())
					{
						// Dispel the fog of war and redraw background symbol
						_fogOfWarB[y][x] = false;
						_renSys->DrawBkgCharColor(y, x, Object::GetInitColorFromBkgMap(lvlBkg->at(y * _settings->lvlSizeX + x)));
					}
				}
	}
}

void Game::RestartLevel()
{
	// Set the inventory at the beginning of the level
	_hero->SetInventory(_inventoryAtLevelStart);

	// Take one heart
	_hero->TakeItem(Item::heart);

	// Restart level
	Initialize();
}

void Game::SetDefaultItemsValueOnLvl()
{
	_crystalsOnLvl = 0;
	_keysOnLvl     = 0;
	_heartsOnLvl   = 0;
}