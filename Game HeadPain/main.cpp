// Library
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "levels.h"
#include "colors.h"
#include <string>

// This file is a temporary solution

// Logic
bool isGameActive = true;
bool fogOfWarB[y_size_lvl][x_size_lvl] {false};

// Objects Map.
// Initially, the idea was to store the addresses of objects, this would allow us to address them directly.
// But this solution does not allow us to effectively remove objects from the vector (most likely, i just don't know how).
// ??? It may be worth making the Objects Map store the ID of objects in a vector.
// ??? This will allow us to access these elements and work with them at the vector level.
// (It seems to me that the solution is temporary).
// -----------------------------------------------------------------
// As a result, i decided to leave the map of objects, but at the same time remove the vector in principle.
Object* objectsMap[y_size_lvl][x_size_lvl];

bool hard = false;

Object* CreateObject(unsigned char symbol, Coord coord);

// Functions
void Start()
{
	int i = 0;
	do
	{
		printf("\nChoose your difficult level (1 - s1mple, 2 - hard): ");
		scanf_s("%i", &i);
	}
	while (i > 2 || i < 1);
	if (i == 2)
		hard = true;
	system("cls");
}

void SetupSystem()
{
	renderSys.Initialize();
}

void RevealFogOfWar(int y_pos, int x_pos)
{
	if (hard == true)
		for (int y = y_pos - 3; y <= y_pos + 3; y++)
			for (int x = x_pos - 3; x <= x_pos + 3; x++)
				fogOfWarB[y][x] = false;
}

void Initialise()
{
	// Clear object map
	for (int y = 0; y < y_size_lvl; y++)
		for (int x = 0; x < x_size_lvl; x++)
			if ((objectsMap[y][x] != _hero) && (objectsMap[y][x] != _empty) && (objectsMap[y][x] != _wall))
				delete objectsMap[y][x];
			
	// Load objects
	for (int y = 0; y < y_size_lvl; y++)
		for (int x = 0; x < x_size_lvl; x++)
		{
			if (hard == true)
				fogOfWarB[y][x] = true;

			// Take symbol from levels map
			unsigned char symbol = levelsData[level][y][x];

			// Create an object
			if (symbol == mapSymbol_hero)
			{
				_hero->SetCoord(x, y);

				// Set hero on objects map
				objectsMap[y][x] = _hero;
			}
			else if (symbol == mapSymbol_empty)
				objectsMap[y][x] = _empty;
			else if (symbol == mapSymbol_wall)
				objectsMap[y][x] = _wall;
			else
			{
				Object* object = CreateObject(symbol, Coord{x,y});

				// Set the object on objects map
				objectsMap[y][x] = object;
			}
					
			switch (symbol)
			{
				case mapSymbol_crystal: CrystalScoreONLVL++; break;
				case mapSymbol_key:     KeyScoreONLVL++;     break;
			}
		}

	// Clear render system
	renderSys.Clear();
	
	// Dispelling the fog of war around the player
	Coord hero_coord = _hero->GetCoord();
	RevealFogOfWar(hero_coord.y, hero_coord.x);
}

void Render()
{
	Inventory heroInventory = _hero->GetInventory();
	Color foreground = Color::black;
	std::string str;

	for (int y = 0; y < y_size_lvl; y++)
	{
		for (int x = 0; x < x_size_lvl; x++)
		{
			if (fogOfWarB[y][x] == false)
			{
				unsigned char renderSymbol = objectsMap[y][x]->GetRenderSymbol();
				Color cellColor = objectsMap[y][x]->GetColor();

				renderSys.DrawChar(y, x, renderSymbol, cellColor);
			}
			else
				renderSys.DrawChar(y, x, mapSymbol_fogOfWar, Color::gray);
		}

		// temp!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		int def_otst = 45;
		char textBuffer[25];

		if (y == 2)
		{
			sprintf_s(textBuffer, "Level %i  ", level + 1);
			foreground = Color::gray;
			renderSys.SendText(y, def_otst, textBuffer, foreground);
		}
		if (y == 3)
		{
			sprintf_s(textBuffer, "Level Key ");
			foreground = Color::blue;
			renderSys.SendText(y, def_otst, textBuffer, foreground);

			foreground = Color::gray;
			if (heroInventory.lvl_key)
				sprintf_s(textBuffer, ": yeap");
			else
				sprintf_s(textBuffer, ": nope");

			renderSys.SendText(y, def_otst + 10, textBuffer, foreground);
		}
		if (y == 4)
		{
			sprintf_s(textBuffer, "Keys");
			foreground = Color::cyan;
			renderSys.SendText(y, def_otst, textBuffer, foreground);

			sprintf_s(textBuffer, ": %i  ", heroInventory.key_count);
			foreground = Color::gray;
			renderSys.SendText(y, def_otst + 4, textBuffer, foreground);
		}
		if (y == 5)
		{
			sprintf_s(textBuffer, "Crystal");
			foreground = Color::darkMagenta;
			renderSys.SendText(y, def_otst, textBuffer, foreground);

			sprintf_s(textBuffer, ": %i  ", heroInventory.crystal_count);
			foreground = Color::gray;
			renderSys.SendText(y, def_otst + 7, textBuffer, foreground);
		}
		if (y == 6)
		{
			sprintf_s(textBuffer, "Crystal");
			foreground = Color::darkMagenta;
			renderSys.SendText(y, def_otst, textBuffer, foreground);

			sprintf_s(textBuffer, " on level: %i  ", CrystalScoreONLVL);
			foreground = Color::gray;
			renderSys.SendText(y, def_otst + 7, textBuffer, foreground);
		}
		if (y == 7)
		{
			sprintf_s(textBuffer, "Key");
			foreground = Color::cyan;
			renderSys.SendText(y, def_otst, textBuffer, foreground);

			sprintf_s(textBuffer, " on level: %i  ", KeyScoreONLVL);
			foreground = Color::gray;
			renderSys.SendText(y, def_otst + 3, textBuffer, foreground);
		}

		Coord heroCoord = _hero->GetCoord();
		if (y == 9) // X coord hero for test
		{
			sprintf_s(textBuffer, "X coord hero: %i  ", heroCoord.x);
			foreground = Color::gray;
			renderSys.SendText(y, def_otst, textBuffer, foreground);
		}
		if (y == 10) // Y coord hero for test
		{
			sprintf_s(textBuffer, "Y coord hero: %i  ", heroCoord.y);
			foreground = Color::gray;
			renderSys.SendText(y, def_otst, textBuffer, foreground);
		}
	}

	renderSys.SendText(y_size_lvl + 1, 4, "Use WASD to move ", Color::gray);
	renderSys.SendText(y_size_lvl + 1, 4+17, "Hero", Color::green);
	renderSys.SendText(y_size_lvl + 2, 4, "Press ", Color::gray);
	renderSys.SendText(y_size_lvl + 2, 4+6, "R ", Color::red);
	renderSys.SendText(y_size_lvl + 2, 4+6+2, "to restart", Color::gray);

	char txtBuffer[25];
	sprintf_s(txtBuffer, "Objects count: %i  ", Object::GetObjectsCount());
	renderSys.SendText(y_size_lvl + 3, 4, txtBuffer, Color::gray);

	// End frame
	renderSys.Render();
}

void RestartLevel()
{
	// Getting inventory !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Inventory heroInventory = hero->GetInventory();

	// Subtract the collected at this level
	//heroInventory.crystal_count -= CrystalScoreCollected;
	//heroInventory.key_count     -= KeyScoreCollected;

	// Resetting the counters of items of this level
	CrystalScoreCollected = 0;
	CrystalScoreONLVL = 0;
	KeyScoreCollected = 0;
	KeyScoreONLVL = 0;

	Initialise();
}

void MoveHeroTo(int y, int x)
{
	Object* collidingObject = objectsMap[y][x];
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
			++CrystalScoreCollected;
			--CrystalScoreONLVL;

			canMove = true;
			break;
		}
		case Entity::key:
		{
			_hero->AddKey();
			++KeyScoreCollected;
			--KeyScoreONLVL;

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
			CrystalScoreONLVL = 0;
			CrystalScoreCollected = 0;
			KeyScoreONLVL = 0;

			isGameActive = false;
			break;
		}
		case Entity::box:
		{
			// Hero move direction
			Coord heroCoord = _hero->GetCoord();
			int heroDirectoinY = y - heroCoord.y;
			int heroDirectionX = x - heroCoord.x;

			// Check space behind the box
			Entity entityBehindBox = objectsMap[y + heroDirectoinY][x + heroDirectionX]->GetEntity();
			if ((entityBehindBox == Entity::empty) 
				|| (entityBehindBox == Entity::crystal)
				|| (entityBehindBox == Entity::key))
			{
				// Bye bye, Crystal !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				if (entityBehindBox == Entity::crystal)
					--CrystalScoreONLVL;

				// Save box adress 
				Object* boxObject = collidingObject;

				// Replace box .........(Пока что так)
				objectsMap[y][x] = _empty;

				// Set box
				objectsMap[y + heroDirectoinY][x + heroDirectionX] = boxObject;

				canMove = true;
			}

			// Logic box for Mines
			if (entityBehindBox == Entity::mine)
			{
				RestartLevel();
			}
			break;
		}
		case Entity::door:
		{
			if (_hero->CheckKey())
			{
				_hero->TakeKey();
				--KeyScoreCollected;

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
		Object* actualObject = objectsMap[y][x];

		// Remove Hero and set Empty
		objectsMap[heroCoord.y][heroCoord.x] = _empty;
		if ((actualObject != _hero) && (actualObject != _empty) && (actualObject != _wall))
			delete actualObject;

		// Set Hero on objects map and set his position
		objectsMap[y][x] = _hero;
		_hero->SetCoord(x, y);

		// Reveal Fog of war
		if (hard == true)
			RevealFogOfWar(y, x);
	}
}

void Move()
{
	unsigned char inputChar = _getch();
	inputChar = tolower(inputChar);

	Coord heroCoord = _hero->GetCoord();

	switch (inputChar)
	{
		// Up
		case 'w': case 230: case 150:
		{
			MoveHeroTo(heroCoord.y - 1, heroCoord.x);
			break;
		}

		// Down
		case 's': case 235: case 155:
		{
			MoveHeroTo(heroCoord.y + 1, heroCoord.x);
			break;
		}

		// Left
		case 'a': case 228: case 148:
		{
			MoveHeroTo(heroCoord.y, heroCoord.x - 1);
			break;
		}

		// Right
		case 'd': case 162: case 130:
		{
			MoveHeroTo(heroCoord.y, heroCoord.x + 1);
			break;
		}

		// Restart level
		case 'r': case 170: case 138:
		{
			RestartLevel();
			break;
		}
		//Inventory heroInventory = hero->GetInventory();
		// Next LVL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		case '2':
		{
			CrystalScoreONLVL     = 0;
			CrystalScoreCollected = 0;
			//heroInventory.key_count = 0;
			++level;

			Initialise();
			break;
		}

		// Back LVL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		case '1':
		{
			CrystalScoreONLVL     = 0;
			CrystalScoreCollected = 0;
			//heroInventory.key_count = 0;
			--level;

			Initialise();
			break;
		}
	}
}

void Shutdown()
{
	system("cls");
	printf("\n\tThank you for playing :) Bye-bye!\n");
	Sleep(3000);
}


int main()
{
	Start();
	SetupSystem();

	while (level != 6)
	{
		Initialise();

		while(isGameActive)
		{
			Render();
			Move();
		}

		level++;
		isGameActive = true;
	}

	Shutdown();
}

Object* CreateObject(unsigned char symbol, Coord coord)
{
	Object* object = new Object(symbol, coord);

	return object;
}