#include "Game.h"
#include <conio.h>

Game::Game() : _isGameActive(false), _hardMode(false), _successfulBkgRead(false),
	_activeLevel(0), _crystalsOnLvl(0), _heartsOnLvl(0), _keysOnLvl(0)
{
	_manager   = new GameManager();
	_settings  = _manager->GetSettings();

	const int renSizeX = _settings->lvlSizeX + _settings->hudMaxSizeX;
	const int renSizeY = _settings->lvlSizeY + _settings->hudMaxSizeY;
	_renSys = new RenderSystem(renSizeY, renSizeX);

	_hero      = new Hero();
	_empty     = new Object(Entity::empty);
	_wall      = new Object(Entity::wall);
	_fogOfWar  = new Object(Entity::fogOfWar);

	_objectsMap = new Object** [_settings->lvlSizeY];
	_fogOfWarB  = new bool* [_settings->lvlSizeY];

	for (int y = 0; y < _settings->lvlSizeY; ++y)
	{
		_objectsMap[y] = new Object* [_settings->lvlSizeX];
		_fogOfWarB[y] = new bool[_settings->lvlSizeX] { false };

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
	delete _fogOfWar;

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
		
		unsigned char inputChar = _getch();
		inputChar = tolower(inputChar);

		switch (inputChar)
		{
			case '1': check = false; break;
			case '2': check = false; _hardMode = true; break;

			default:
			_renSys->SendText(2, 4, "Just choose mode -_-", static_cast<Color>(rand() % 15 + 1));	// 15 Colors (without black)
			_renSys->Render();
		}
	}
}

void Game::SetupSettings()
{
	// Setting up the inventory
	_hero->SetItem(Item::heart, _hardMode == true ? _settings->hardStartHearts : _settings->startHearts);
}

void Game::ClearObjectMap()
{
	for (int y = 0; y < _settings->lvlSizeY; ++y)
		for (int x = 0; x < _settings->lvlSizeX; ++x)
			if ((_objectsMap[y][x] != _hero) && (_objectsMap[y][x] != _empty) && (_objectsMap[y][x] != _wall))
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
			if (_hardMode == true)
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
			else
			{
				Object* object = CreateObject(symbol, Coord{ x,y });

				// Set the object on objects map
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
		if (_hardMode == false)
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
	DispelFogOfWar(hero_coord.y, hero_coord.x);
}

void Game::Render()
{
	for (int y = 0; y < _settings->lvlSizeY; ++y)
		for (int x = 0; x < _settings->lvlSizeX; ++x)
			if (_fogOfWarB[y][x] == false)
				_renSys->DrawChar(y, x, _objectsMap[y][x]->GetRenderObject());
			else
				_renSys->DrawChar(y, x, _fogOfWar->GetRenderObject());

	RenderHud();
	_renSys->Render();
}

void Game::RenderHud()
{
	static char textBuffer[25];

	Inventory inv = _hero->GetInventory();
	const int _indentX = _settings->lvlSizeX + _settings->hudIndentX;

	// GLHF
	sprintf_s(textBuffer, "Level %i  ", _activeLevel + 1);
	_renSys->SendText(2, _indentX, textBuffer);

	sprintf_s(textBuffer, "Level Key");
	_renSys->SendText(4, _indentX, textBuffer, Color::blue);
	inv.lvlKey == true ? sprintf_s(textBuffer, ": yeap") : sprintf_s(textBuffer, ": nope");
	_renSys->SendText(4, _indentX + 9, textBuffer);
	
	sprintf_s(textBuffer, "Keys");
	_renSys->SendText(5, _indentX, textBuffer, Color::cyan);
	sprintf_s(textBuffer, ": %i  ", inv.keys);
	_renSys->SendText(5, _indentX + 4, textBuffer);
	
	sprintf_s(textBuffer, "Hearts");
	_renSys->SendText(6, _indentX, textBuffer, Color::red);
	sprintf_s(textBuffer, ": %i  ", inv.hearts);
	_renSys->SendText(6, _indentX + 6, textBuffer);

	sprintf_s(textBuffer, "Crystals");
	_renSys->SendText(7, _indentX, textBuffer, Color::darkMagenta);
	sprintf_s(textBuffer, ": %i  ", inv.crystals);
	_renSys->SendText(7, _indentX + 7, textBuffer);

	sprintf_s(textBuffer, "Keys");
	_renSys->SendText(9, _indentX, textBuffer, Color::cyan);
	sprintf_s(textBuffer, "on level: %i  ", _keysOnLvl);
	_renSys->SendText(9, _indentX + 5, textBuffer);

	sprintf_s(textBuffer, "Hearts");
	_renSys->SendText(10, _indentX, textBuffer, Color::red);
	sprintf_s(textBuffer, "on level: %i  ", _heartsOnLvl);
	_renSys->SendText(10, _indentX + 7, textBuffer);

	sprintf_s(textBuffer, "Crystals");
	_renSys->SendText(11, _indentX, textBuffer, Color::darkMagenta);
	sprintf_s(textBuffer, "on level: %i  ", _crystalsOnLvl);
	_renSys->SendText(11, _indentX + 9, textBuffer);

	sprintf_s(textBuffer, "X coord hero: %i  ", _hero->GetCoord().x);
	_renSys->SendText(13, _indentX, textBuffer);
	sprintf_s(textBuffer, "Y coord hero: %i  ", _hero->GetCoord().y);
	_renSys->SendText(14, _indentX, textBuffer);

	sprintf_s(textBuffer, "Objects count: %i  ", Object::GetObjectsCount());
	_renSys->SendText(16, _indentX, textBuffer);

	_renSys->SendText(_settings->lvlSizeY + 1, 4, "Use WASD to move ");
	_renSys->SendText(_settings->lvlSizeY + 1, 4 + 17, "Hero", Color::green);
	_renSys->SendText(_settings->lvlSizeY + 2, 4, "Press R to restart level.");
	_renSys->SendText(_settings->lvlSizeY + 2, 4 + 6, "R", Color::red);
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

void Game::Move()
{
	//if (!_kbhit())
		//return;

	unsigned char inputChar = _getch();
	inputChar = tolower(inputChar);

	Coord heroCoord = _hero->GetCoord();

	if (inputChar == 0 || inputChar == 224)	// for special keys
		switch (_getch())
		{
			// Up Down Left Right for arrays
			case 72:	MoveHeroTo(heroCoord.y - 1, heroCoord.x);	break;
			case 80:	MoveHeroTo(heroCoord.y + 1, heroCoord.x);	break;
			case 75:	MoveHeroTo(heroCoord.y, heroCoord.x - 1);	break;
			case 77:	MoveHeroTo(heroCoord.y, heroCoord.x + 1);   break;
		}
	else
		switch (inputChar)
		{
			// Up Down Left Right
			case 'w': case 230: case 150:	MoveHeroTo(heroCoord.y - 1, heroCoord.x);	break;
			case 's': case 235: case 155:	MoveHeroTo(heroCoord.y + 1, heroCoord.x);	break;
			case 'a': case 228: case 148:	MoveHeroTo(heroCoord.y, heroCoord.x - 1);	break;
			case 'd': case 162: case 130:	MoveHeroTo(heroCoord.y, heroCoord.x + 1);   break;

			case 'r': case 170: case 138:	RestartLevel();   break;	// Restart level
			case '2':	_activeLevel++;		Initialize();	  break;	// Next level
			case '1':	_activeLevel--;		Initialize();	  break;	// Back level
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
					delete _objectsMap[objBehindY][objBehindX];
				else
					switch (entityBehindBox)
					{
						case Entity::crystal:	_crystalsOnLvl--;    break;
						case Entity::heart:		_heartsOnLvl--;		 break;
						case Entity::key:       _keysOnLvl--;        break;
						case Entity::levelKey:  break;
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
		if ((actualObject != _hero) && (actualObject != _empty) && (actualObject != _fogOfWar))
			delete actualObject;

		// Set Hero on objects map and set his position
		_objectsMap[y][x] = _hero;
		_hero->SetCoord(x, y);

		// Dispel Fog of war
		if (_hardMode == true)
			DispelFogOfWar(y, x);
	}
}

void Game::DispelFogOfWar(int y_pos, int x_pos)
{
	if ((_hardMode == true) && (_successfulBkgRead = true))
	{
		const std::string* lvlBkg(_manager->GetLastLevel());
		for (int y = y_pos - 2; y <= y_pos + 2; y++)
			for (int x = x_pos - 3; x <= x_pos + 3; x++)
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

void Game::SetDefaultItemsValueOnLvl()
{
	_crystalsOnLvl = 0;
	_keysOnLvl = 0;
}