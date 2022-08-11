#include "Game.h"

#include <iostream>
#include <conio.h>

Game::Game() : _isGameActive(false), _hardMode(false),
	_activeLevel(0)
{
	_renSys   = new RenderSystem();

	_hero     = new Hero();
	_empty    = new Object(Entity::empty);
	_wall     = new Object(Entity::wall);
	_fogOfWar = new Object(Entity::fogOfWar);
}

Game::~Game()
{
	delete _renSys;

	delete _hero;
	delete _empty;
	delete _wall;
	delete _fogOfWar;
}

void Game::Start()
{
	ChooseMode();
	_isGameActive = true;

	while (_activeLevel != _levelsCount)
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

void Game::Initialize()
{
	// Set default items value on this level
	SetDefaultItemsValueOnLvl();

	// Clear object map
	for (int y = 0; y < _lvlSizeY; y++)
		for (int x = 0; x < _lvlSizeX; x++)
			if ((_objectsMap[y][x] != _hero) && (_objectsMap[y][x] != _empty) && (_objectsMap[y][x] != _wall)
				&& _objectsMap[y][x] != nullptr)
				delete _objectsMap[y][x];

	// Load objects
	for (int y = 0; y < _lvlSizeY; y++)
		for (int x = 0; x < _lvlSizeX; x++)
		{
			if (_hardMode == true)
				_fogOfWarB[y][x] = true;

			// Take symbol from levels map
			unsigned char symbol = levelsData[_activeLevel][y][x];

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
				case Entity::key:        _keysOnLvl++;        break;
			}
		}

	// Clear render system
	_renSys->Clear();

	// Render Background if hardMode is false
	if (_hardMode == false)
		for (int y = 0; y < _lvlSizeY; ++y)
			for (int x = 0; x < _lvlSizeX; ++x)
				_renSys->DrawBackground(y, x, Object::GetInitializeColorBackgroundFromMap(levelsBackgroundData[_activeLevel][y][x]));

	// Remember the inventory state at the level start
	_inventoryAtLevelStart = _hero->GetInventory();

	// Dispelling the fog of war around the player
	Coord hero_coord = _hero->GetCoord();
	DispelFogOfWar(hero_coord.y, hero_coord.x);
}

void Game::Render()
{
	for (int y = 0; y < _lvlSizeY; y++)
		for (int x = 0; x < _lvlSizeX; x++)
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

	Inventory inventory = _hero->GetInventory();

	// GLHF
	sprintf_s(textBuffer, "Level %i  ", _activeLevel + 1);
	_renSys->SendText(2, _indentX, textBuffer);

	sprintf_s(textBuffer, "Level Key");
	_renSys->SendText(4, _indentX, textBuffer, Color::blue);
	inventory.lvl_key == true ? sprintf_s(textBuffer, ": yeap") : sprintf_s(textBuffer, ": nope");
	_renSys->SendText(4, _indentX + 9, textBuffer);
	
	sprintf_s(textBuffer, "Keys");
	_renSys->SendText(5, _indentX, textBuffer, Color::cyan);
	sprintf_s(textBuffer, ": %i  ", inventory.key_count);
	_renSys->SendText(5, _indentX + 4, textBuffer);
	
	sprintf_s(textBuffer, "Crystals");
	_renSys->SendText(6, _indentX, textBuffer, Color::darkMagenta);
	sprintf_s(textBuffer, ": %i  ", inventory.crystal_count);
	_renSys->SendText(6, _indentX + 7, textBuffer);

	sprintf_s(textBuffer, "Crystals");
	_renSys->SendText(7, _indentX, textBuffer, Color::darkMagenta);
	sprintf_s(textBuffer, " on level: %i  ", _crystalsOnLvl);
	_renSys->SendText(7, _indentX + 7, textBuffer);

	sprintf_s(textBuffer, "Keys");
	_renSys->SendText(8, _indentX, textBuffer, Color::cyan);
	sprintf_s(textBuffer, " on level: %i  ", _keysOnLvl);
	_renSys->SendText(8, _indentX + 3, textBuffer);

	sprintf_s(textBuffer, "X coord hero: %i  ", _hero->GetCoord().x);
	_renSys->SendText(10, _indentX, textBuffer);
	sprintf_s(textBuffer, "Y coord hero: %i  ", _hero->GetCoord().y);
	_renSys->SendText(11, _indentX, textBuffer);

	sprintf_s(textBuffer, "Objects count: %i  ", Object::GetObjectsCount());
	_renSys->SendText(13, _indentX, textBuffer);

	_renSys->SendText(_lvlSizeY + 1, 4, "Use WASD to move ");
	_renSys->SendText(_lvlSizeY + 1, 4 + 17, "Hero", Color::green);
	_renSys->SendText(_lvlSizeY + 2, 4, "Press R to restart level.");
	_renSys->SendText(_lvlSizeY + 2, 4 + 6, "R", Color::red);
}

void Game::RestartLevel()
{
	// Set the inventory at the beginning of the level
	_hero->SetInventory(_inventoryAtLevelStart);

	// Restart level
	Initialize();
}

void Game::Move()
{
	unsigned char inputChar = _getch();
	inputChar = tolower(inputChar);

	Coord heroCoord = _hero->GetCoord();

	switch (inputChar)
	{
		// Up Down Left Right
		case 'w': case 230: case 150:	MoveHeroTo(heroCoord.y - 1, heroCoord.x);	break;
		case 's': case 235: case 155:	MoveHeroTo(heroCoord.y + 1, heroCoord.x);	break;
		case 'a': case 228: case 148:	MoveHeroTo(heroCoord.y, heroCoord.x - 1);	break;
		case 'd': case 162: case 130:	MoveHeroTo(heroCoord.y, heroCoord.x + 1);   break;

		// Restart level
		case 'r': case 170: case 138:	RestartLevel();   break;
	
		// Next level
		case '2':	_activeLevel++;		Initialize();	  break;

		// Back level
		case '1':	_activeLevel--;		Initialize();	  break;
	}
}

void Game::MoveHeroTo(int y, int x)
{
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
			_hero->AddCrystal();
			_crystalsOnLvl--;

			canMove = true;
			break;
		}
		case Entity::key:
		{
			_hero->AddKey();
			_keysOnLvl--;

			canMove = true;
			break;
		}
		case Entity::levelKey:
		{
			_hero->GiveLvlKey();

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
			int heroDirectoinY = y - heroCoord.y;
			int heroDirectionX = x - heroCoord.x;

			// Check space behind the box
			// and handling collisions with objects
			Entity entityBehindBox = _objectsMap[y + heroDirectoinY][x + heroDirectionX]->GetEntity();
			if ((entityBehindBox == Entity::empty)
				|| (entityBehindBox == Entity::crystal)
				|| (entityBehindBox == Entity::key))
			{
				// Bye bye, Object
				if (entityBehindBox != Entity::empty)
					delete _objectsMap[y + heroDirectoinY][x + heroDirectionX];

				switch (entityBehindBox)
				{
					case Entity::key:         _keysOnLvl--;        break;
					case Entity::levelKey:    break;
					case Entity::crystal:     _crystalsOnLvl--;    break;
				}

				// Replace box
				Object* boxObject = collidingObject;
				_objectsMap[y][x] = _empty;
				_objectsMap[y + heroDirectoinY][x + heroDirectionX] = boxObject;

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
				_hero->TakeKey();

				canMove = true;
				break;
			}
		}
		case Entity::levelDoor:
		{
			if (_hero->CheckLvlkey())
			{
				_hero->TakeLvlKey();

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

		// Reveal Fog of war
		if (_hardMode == true)
			DispelFogOfWar(y, x);
	}
}

void Game::Shutdown()
{
	system("cls");
	printf("\n\tThank you for playing :) Bye-bye!\n");
	Sleep(3000);

}

void Game::DispelFogOfWar(int y_pos, int x_pos)
{
	if (_hardMode == true)
		for (int y = y_pos - 2; y <= y_pos + 2; y++)
			for (int x = x_pos - 3; x <= x_pos + 3; x++)
				if (x < _lvlSizeX && y < _lvlSizeY && x >= 0 && y >= 0)
					if (_fogOfWarB[y][x] == true)
					{
						// Dispel the fog of war and redraw background symbol
						_fogOfWarB[y][x] = false;
						_renSys->DrawBackground(y, x, Object::GetInitializeColorBackgroundFromMap(levelsBackgroundData[_activeLevel][y][x]));
					}
}

Object* Game::CreateObject(unsigned char symbol, Coord coord)
{
	return new Object(symbol, coord);
}

void Game::SetDefaultItemsValueOnLvl()
{
	_crystalsOnLvl = 0;
	_keysOnLvl = 0;
}

void Game::ChooseMode()
{
	int i = 0;

	do
	{
		std::cout << "\n Choose mode (1 - s1mple, 2 - hard): ";
		std::cin >> i;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		if (i > 2 || i < 1)
		{
			std::cout << " Just choose mode -_- ";
		}
	} while (i > 2 || i < 1);

	if (i == 2)
		_hardMode = true;

	system("cls");
}
