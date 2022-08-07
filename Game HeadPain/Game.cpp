#include "Game.h"

#include <iostream>
#include <conio.h>

Game::Game() : _isGameActive(false), _hardMode(false),
	_activeLevel(0)
{
	_renSys = new RenderSystem();

	_hero  = new Hero();
	_empty = new Object(' ');
	_wall  = new Object('#');
}

Game::~Game()
{
	delete _renSys;

	delete _hero;
	delete _empty;
	delete _wall;
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
				fogOfWarB[y][x] = true;

			// Take symbol from levels map
			unsigned char symbol = levelsData[_activeLevel][y][x];

			// Create an object
			if (symbol == mapSymbol_hero)
			{
				_hero->SetCoord(x, y);

				// Set hero on objects map
				_objectsMap[y][x] = _hero;
			}
			else if (symbol == mapSymbol_empty)
				_objectsMap[y][x] = _empty;
			else if (symbol == mapSymbol_wall)
				_objectsMap[y][x] = _wall;
			else
			{
				Object* object = CreateObject(symbol, Coord{ x,y });

				// Set the object on objects map
				_objectsMap[y][x] = object;
			}

			switch (symbol)
			{
				case mapSymbol_crystal: _crystalsOnLvl++; break;
				case mapSymbol_key:     _keysOnLvl++;     break;
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
	Inventory heroInventory = _hero->GetInventory();
	Color foreground = Color::black;
	std::string str;

	for (int y = 0; y < _lvlSizeY; y++)
	{
		for (int x = 0; x < _lvlSizeX; x++)
		{
			if (fogOfWarB[y][x] == false)
			{
				RenderObject renderObj = _objectsMap[y][x]->GetRenderObject();
				_renSys->DrawChar(y, x, renderObj);
			}
			else
			{
				RenderObject r_fogOfWar{ mapSymbol_fogOfWar, Color::gray, Color::black };
				_renSys->DrawChar(y, x, r_fogOfWar);
			}
		}

		// temp!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		int def_otst = 45;
		char textBuffer[25];

		if (y == 2)
		{
			sprintf_s(textBuffer, "Level %i  ", _activeLevel + 1);
			foreground = Color::gray;
			_renSys->SendText(y, def_otst, textBuffer, foreground);
		}
		if (y == 3)
		{
			sprintf_s(textBuffer, "Level Key");
			foreground = Color::blue;
			_renSys->SendText(y, def_otst, textBuffer, foreground);

			foreground = Color::gray;
			if (heroInventory.lvl_key)
				sprintf_s(textBuffer, ": yeap");
			else
				sprintf_s(textBuffer, ": nope");

			_renSys->SendText(y, def_otst + 10, textBuffer, foreground);
		}
		if (y == 4)
		{
			sprintf_s(textBuffer, "Keys");
			foreground = Color::cyan;
			_renSys->SendText(y, def_otst, textBuffer, foreground);

			sprintf_s(textBuffer, ": %i  ", heroInventory.key_count);
			foreground = Color::gray;
			_renSys->SendText(y, def_otst + 4, textBuffer, foreground);
		}
		if (y == 5)
		{
			sprintf_s(textBuffer, "Crystal");
			foreground = Color::darkMagenta;
			_renSys->SendText(y, def_otst, textBuffer, foreground);

			sprintf_s(textBuffer, ": %i  ", heroInventory.crystal_count);
			foreground = Color::gray;
			_renSys->SendText(y, def_otst + 7, textBuffer, foreground);
		}
		if (y == 6)
		{
			sprintf_s(textBuffer, "Crystal");
			foreground = Color::darkMagenta;
			_renSys->SendText(y, def_otst, textBuffer, foreground);

			sprintf_s(textBuffer, " on level: %i  ", _crystalsOnLvl);
			foreground = Color::gray;
			_renSys->SendText(y, def_otst + 7, textBuffer, foreground);
		}
		if (y == 7)
		{
			sprintf_s(textBuffer, "Key");
			foreground = Color::cyan;
			_renSys->SendText(y, def_otst, textBuffer, foreground);

			sprintf_s(textBuffer, " on level: %i  ", _keysOnLvl);
			foreground = Color::gray;
			_renSys->SendText(y, def_otst + 3, textBuffer, foreground);
		}

		Coord heroCoord = _hero->GetCoord();
		if (y == 9) // X coord hero for test
		{
			sprintf_s(textBuffer, "X coord hero: %i  ", heroCoord.x);
			foreground = Color::gray;
			_renSys->SendText(y, def_otst, textBuffer, foreground);
		}
		if (y == 10) // Y coord hero for test
		{
			sprintf_s(textBuffer, "Y coord hero: %i  ", heroCoord.y);
			foreground = Color::gray;
			_renSys->SendText(y, def_otst, textBuffer, foreground);
		}
	}

	_renSys->SendText(_lvlSizeY + 1, 4, "Use WASD to move ", Color::gray);
	_renSys->SendText(_lvlSizeY + 1, 4+17, "Hero", Color::green);
	_renSys->SendText(_lvlSizeY + 2, 4, "Press ", Color::gray);
	_renSys->SendText(_lvlSizeY + 2, 4+6, "R ", Color::red);
	_renSys->SendText(_lvlSizeY + 2, 4+6+2, "to restart", Color::gray);

	char txtBuffer[25];
	sprintf_s(txtBuffer, "Objects count: %i  ", Object::GetObjectsCount());
	_renSys->SendText(_lvlSizeY + 3, 4, txtBuffer, Color::gray);

	// End frame
	_renSys->Render();
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
				case Entity::key:         _keysOnLvl;        break;
				case Entity::levelKey:    break;
				case Entity::crystal:     _crystalsOnLvl;    break;
				}


				// Save box adress 
				Object* boxObject = collidingObject;

				// Replace box .........(Пока что так)
				_objectsMap[y][x] = _empty;

				// Set box
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
		if ((actualObject != _hero) && (actualObject != _empty))
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
				if (fogOfWarB[y][x] == true)
				{
					// Dispel the fog of war
					// and redraw background symbol
					fogOfWarB[y][x] = false;
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
