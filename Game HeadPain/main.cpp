// Library
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "levels.h"
#include "consoleColor//console_colors.h"
#include <string>

// This file is a temporary solution

// Logic
bool isGameActive = true;
unsigned char levelMap[y_size_lvl][x_size_lvl];
bool fogOfWarB[y_size_lvl][x_size_lvl];

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
void DeleteObject(Object* object);

// Functions
void Start()
{
	int i = 0;
	printf("\t\n");
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
	{
		for (int y = y_pos - 3; y <= y_pos + 3; y++)
			for (int x = x_pos - 3; x <= x_pos + 3; x++)
				fogOfWarB[y][x] = false;
	}
}

void Initialise()
{
	// Load objects
	for (int y = 0; y < y_size_lvl; y++)
	{
		for (int x = 0; x < x_size_lvl; x++)
		{
			if (hard == true)
				fogOfWarB[y][x] = true;
			else
				fogOfWarB[y][x] = false;

			unsigned char symbol = levelsData[level][y][x];

			// Create an object
			if (symbol == mapSymbol_hero)
			{
				hero->SetCoord(x, y);

				// Set hero on objects map
				objectsMap[y][x] = hero;
			}
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
	}

	// Dispelling the fog of war around the player
	Coord hero_coord = hero->GetCoord();
	RevealFogOfWar(hero_coord.y, hero_coord.x);
}

void Render()
{
	Inventory heroInventory = hero->GetInventory();
	ccolors::Color background = ccolors::Color::black;
	ccolors::Color foreground = ccolors::Color::black;
	std::string str;

	for (int y = 0; y < y_size_lvl; y++)
	{
		for (int x = 0; x < x_size_lvl; x++)
		{
			//printf("\n\t");

			if (fogOfWarB[y][x] == false)
			{
				unsigned char renderSymbol = objectsMap[y][x]->GetRenderSymbol();
				ccolors::Color cellColor   = objectsMap[y][x]->GetColor();

				renderSys.DrawChar(y, x, renderSymbol, cellColor, ccolors::Color::black);
			}
			else
				renderSys.DrawChar(y, x, mapSymbol_fogOfWar, ccolors::Color::gray, ccolors::Color::black);
		}

		// temp!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		int def_otst = 45;

		if (y == 2)
		{
			str = "Level " + (level + 1);
			foreground = ccolors::Color::gray;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);
		}
		if (y == 3)
		{
			str = "Level Key ";
			foreground = ccolors::Color::blue;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);

			foreground = ccolors::Color::gray;
			if (heroInventory.lvl_key)
				str = ": yeap";
			else
				str = ": nope";

			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);
		}
		if (y == 4)
		{
			str = "Keys";
			foreground = ccolors::Color::cyan;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);

			str = ": " + heroInventory.key_count;
			foreground = ccolors::Color::gray;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);
		}
		if (y == 5)
		{
			str = "Crystal";
			foreground = ccolors::Color::darkMagenta;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);

			str = ": " + heroInventory.crystal_count;
			foreground = ccolors::Color::gray;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);
		}
		if (y == 6)
		{
			str = "Crystal";
			foreground = ccolors::Color::darkMagenta;
			renderSys.DrawTextW(y, def_otst, "Crystal", foreground, background);

			str = " on level: " + CrystalScoreONLVL;
			foreground = ccolors::Color::gray;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);
		}
		if (y == 7)
		{
			str = "Key";
			foreground = ccolors::Color::cyan;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);

			str = " on level: " + KeyScoreONLVL;
			foreground = ccolors::Color::gray;
			renderSys.DrawTextW(y, def_otst + 3, str.c_str(), foreground, background);
		}

		Coord heroCoord = hero->GetCoord();
		if (y == 9) // X coord hero for test
		{
			str = "X coord hero: " + std::to_string(heroCoord.x);
			foreground = ccolors::Color::gray;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);
		}
		if (y == 10) // Y coord hero for test
		{
			str = "Y coord hero: " + std::to_string(heroCoord.y);
			foreground = ccolors::Color::gray;
			renderSys.DrawTextW(y, def_otst, str.c_str(), foreground, background);
		}

		//if (y == 2)
		//{
		//	str = "\t Level " + (level + 1);

		//	ccolors::SetColor(ccolors::Color::gray);
		//	sprintf(str, "   Level %i  ", level + 1);
		//}

		//if (y == 3)
		//{
		//	ccolors::SetColor(ccolors::Color::blue);
		//	printf("   Level Key ");
		//	ccolors::SetColor(ccolors::Color::gray);
		//	if (heroInventory.lvl_key == true)
		//		printf(": yeap  ");
		//	else
		//		printf(": nope  ");
		//}

		//if (y == 4)
		//{
		//	ccolors::SetColor(ccolors::Color::cyan);
		//	printf("   Key ");
		//	ccolors::SetColor(ccolors::Color::gray);
		//	printf(": %i  ", heroInventory.key_count);
		//}

		//if (y == 5)
		//{
		//	ccolors::SetColor(ccolors::Color::darkMagenta);
		//	printf("   Crystal");
		//	ccolors::SetColor(ccolors::Color::gray);
		//	printf(": %i  \t", heroInventory.crystal_count);
		//}

		//if (y == 6)
		//{
		//	ccolors::SetColor(ccolors::Color::darkMagenta);
		//	printf("   Crystal");
		//	ccolors::SetColor(ccolors::Color::gray);
		//	printf(" on level: %i   ", CrystalScoreONLVL);
		//}

		//if (y == 7)
		//{
		//	ccolors::SetColor(ccolors::Color::darkMagenta);
		//	printf("   Key");
		//	ccolors::SetColor(ccolors::Color::gray);
		//	printf(" on level: %i   ", KeyScoreONLVL);
		//}

		//Coord heroCoord = hero->GetCoord();
		//if (y == 9) // X coord hero for test
		//{
		//	ccolors::SetColor(ccolors::Color::gray);
		//	printf("   X coord hero: %i   ", heroCoord.x);
		//}
		//if (y == 10) // Y coord hero for test
		//{
		//	ccolors::SetColor(ccolors::Color::gray);
		//	printf("   Y coord hero: %i   ", heroCoord.y);
		//}
	}

	//printf("\n\tUse WASD to move ");
	//ccolors::SetColor(ccolors::Color::green);
	//printf("Hero");
	//ccolors::SetColor(ccolors::Color::gray);
	//printf(". Press ");
	//ccolors::SetColor(ccolors::Color::red);
	//printf("R");
	//ccolors::SetColor(ccolors::Color::gray);
	//printf(" to restart.\n");

	//printf("Objects count: %i", Object::GetObjectsCount());

	renderSys.DrawTextW(y_size_lvl + 1, 4, "Use WASD to move ", ccolors::Color::gray, background);
	renderSys.DrawTextW(y_size_lvl + 1, 4+22, "Hero", ccolors::Color::green, background);
	renderSys.DrawTextW(y_size_lvl + 2, 4, "Press ", ccolors::Color::gray, background);
	renderSys.DrawTextW(y_size_lvl + 2, 4+6, "R ", ccolors::Color::red, background);
	renderSys.DrawTextW(y_size_lvl + 2, 4+6+2, "to restart", ccolors::Color::gray, background);
	renderSys.DrawTextW(y_size_lvl + 3, 4, "Objects count: " + Object::GetObjectsCount(), ccolors::Color::gray, background);

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
			hero->AddCrystal();
			++CrystalScoreCollected;
			--CrystalScoreONLVL;

			canMove = true;
			break;
		}

		case Entity::key:
		{
			hero->AddKey();
			++KeyScoreCollected;
			--KeyScoreONLVL;

			canMove = true;
			break;
		}
		case Entity::levelKey:
		{
			hero->GiveLvlKey();

			canMove = true;
			break;
		}

		// Mine
		case Entity::mine:
		{
			RestartLevel();
			break;
		}

		// Exit
		case Entity::exitDoor:
		{
			CrystalScoreONLVL = 0;
			CrystalScoreCollected = 0;
			KeyScoreONLVL = 0;

			isGameActive = false;
			break;
		}

		// Box
		case Entity::box:
		{
			// Hero move direction
			Coord heroCoord = hero->GetCoord();
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
				Object* boxObject = objectsMap[y][x];

				// Replace box .........(Пока что так)
				objectsMap[y][x] = objectsMap[y + heroDirectoinY][x + heroDirectionX];

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

		// Door
		case Entity::door:
		{
			if (hero->CheckKey())
			{
				hero->TakeKey();
				KeyScoreONLVL--;

				canMove = true;
				break;
			}
		}

		// Level Door
		case Entity::levelDoor:
		{
			if (hero->CheckLvlkey())
			{
				hero->TakeLvlKey();

				canMove = true;
				break;
			}
		}

	}

	if (canMove)
	{
		Coord heroCoord = hero->GetCoord();

		// Remove Hero and set Empty
		objectsMap[heroCoord.y][heroCoord.x] = objectsMap[y][x];

		// Set Hero position
		hero->SetCoord(x, y);

		// Set Hero
		objectsMap[y][x] = hero;

		// Reveal Fog of war
		if (hard == true)
			RevealFogOfWar(y, x);
	}
}

void Move()
{
	unsigned char inputChar = _getch();
	inputChar = tolower(inputChar);

	Coord heroCoord = hero->GetCoord();

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
			level++;

			Initialise();
			break;
		}

		// Back LVL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		case '1':
		{
			CrystalScoreONLVL = 0;
			CrystalScoreCollected = 0;
			//heroInventory.key_count = 0;
			level--;

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

	do
	{
		SetupSystem();
		Initialise();
		do
		{
			Render();
			Move();
		}
		while (isGameActive);
		system("cls");
		level++;
		isGameActive = true;
	}
	while (level != 6);

	Shutdown();
}

Object* CreateObject(unsigned char symbol, Coord coord)
{
	Object* object = new Object(symbol, coord);

	return object;
}

void DeleteObject(Object* object)
{
	delete object;
}