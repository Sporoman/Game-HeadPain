// Library
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "levels.h"
#include "consoleColor//text_work.h"

// This file is a temporary solution

// Logic
bool isGameActive = true;
unsigned char levelMap[game_info::y_size_lvl][game_info::x_size_lvl];
Object* objectsMap[game_info::y_size_lvl][game_info::x_size_lvl];
bool fogOfWarB[game_info::y_size_lvl][game_info::x_size_lvl];

bool hard = false;

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
	ccolor::HideCursor();
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
	for (int y = 0; y < game_info::y_size_lvl; y++)
	{
		for (int x = 0; x < game_info::x_size_lvl; x++)
		{
			if (hard == true)
				fogOfWarB[y][x] = true;
			else
				fogOfWarB[y][x] = false;

			unsigned char symbol = game_info::levelsData[game_info::level][y][x];

			// Create an object
			if (symbol == game_info::mapSymbol_hero)
			{
				game_info::hero->SetCoord(x, y);

				// Set hero on objects map
				objectsMap[y][x] = game_info::hero;
			}
			else
			{
				Object* object = game_info::CreateObjectInVector(symbol);
				object->SetCoord(x, y);

				// Set the object on objects map
				objectsMap[y][x] = object;
			}
					
			switch (symbol)
			{
				case game_info::mapSymbol_crystal: game_info::CrystalScoreONLVL++; break;
			}
		}
	}

	// Dispelling the fog of war around the player
	Coord hero_coord = game_info::hero->GetCoord();
	RevealFogOfWar(hero_coord.y, hero_coord.x);
}

void Render()
{
	// Cursor to (0,0)
	ccolor::SetCursor(0, 0);

	printf("\n\t");
	for (int y = 0; y < game_info::y_size_lvl; y++)
	{
		for (int x = 0; x < game_info::x_size_lvl; x++)
		{
			if (fogOfWarB[y][x] == false)
			{
				// Нужно не забыть о координатах объекта, мапы объектов и рендера (ну пока так :) )
				unsigned char renderSymbol = objectsMap[y][x]->GetRenderSymbol();
				ccolor::Color cellColor    = objectsMap[y][x]->GetColor();

				ccolor::SetColor(cellColor);
				printf("%c", renderSymbol);
			}
			else
			{
				ccolor::SetColor(ccolor::Color::gray);
				printf("%c", game_info::mapSymbol_fogOfWar);
			}
		}

		Inventory heroInventory = game_info::hero->GetInventory();

		if (y == 2)
		{
			ccolor::SetColor(ccolor::Color::gray);
			printf("   Level %i  ", game_info::level + 1);
		}

		if (y == 3)
		{
			ccolor::SetColor(ccolor::Color::blue);
			printf("   Level Key ");
			ccolor::SetColor(ccolor::Color::gray);
			if (heroInventory.lvl_key == true)
				printf(": yeap  ");
			else
				printf(": nope  ");
		}

		if (y == 4)
		{
			ccolor::SetColor(ccolor::Color::cyan);
			printf("   Key ");
			ccolor::SetColor(ccolor::Color::gray);
			printf(": %i  ", heroInventory.key_count);
		}

		if (y == 5)
		{
			ccolor::SetColor(ccolor::Color::darkMagenta);
			printf("   Crystal");
			ccolor::SetColor(ccolor::Color::gray);
			printf(": %i  \t", heroInventory.crystal_count);
		}

		if (y == 6)
		{
			ccolor::SetColor(ccolor::Color::darkMagenta);
			printf("   Crystal");
			ccolor::SetColor(ccolor::Color::gray);
			printf(" on level: %i   ", game_info::CrystalScoreONLVL);
		}

		Coord heroCoord = game_info::hero->GetCoord();
		if (y == 9) // X coord hero for test
		{
			ccolor::SetColor(ccolor::Color::gray);
			printf("   X coord hero: %i   ", heroCoord.x);
		}
		if (y == 10) // Y coord hero for test
		{
			ccolor::SetColor(ccolor::Color::gray);
			printf("   Y coord hero: %i   ", heroCoord.y);
		}
		printf("\n\t");
	}
	printf("\n\tUse WASD to move ");
	ccolor::SetColor(ccolor::Color::green);
	printf("Hero");
	ccolor::SetColor(ccolor::Color::gray);
	printf(". Press ");
	ccolor::SetColor(ccolor::Color::red);
	printf("R");
	ccolor::SetColor(ccolor::Color::gray);
	printf(" to restart.\n");

	printf("Objects count: %i", game_info::objects.size());
}

void RestartLevel()
{
	Inventory heroInventory = game_info::hero->GetInventory();

	heroInventory.crystal_count -= game_info::CrystalScoreCollected;
	game_info::CrystalScoreCollected = 0;
	game_info::CrystalScoreONLVL = 0;
	heroInventory.key_count -= game_info::KeyScoreONLVL;
	game_info::KeyScoreONLVL = 0;

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
			game_info::hero->AddCrystal();
			++game_info::CrystalScoreCollected;
			--game_info::CrystalScoreONLVL;

			canMove = true;
			break;
		}

		case Entity::key:
		{
			game_info::hero->AddKey();
			game_info::KeyScoreONLVL;

			canMove = true;
			break;
		}
		case Entity::levelKey:
		{
			game_info::hero->GiveLvlKey();

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
			game_info::CrystalScoreONLVL = 0;
			game_info::CrystalScoreCollected = 0;
			game_info::KeyScoreONLVL = 0;

			isGameActive = false;
			break;
		}

		// Box
		case Entity::box:
		{
			// Hero move direction
			Coord heroCoord = game_info::hero->GetCoord();
			int heroDirectoinY = y - heroCoord.y;
			int heroDirectionX = x - heroCoord.x;


			// Check space behind the box
			Entity entityBehindBox = objectsMap[y + heroDirectoinY][x + heroDirectionX]->GetEntity();
			if ((entityBehindBox == Entity::empty) 
				|| (entityBehindBox == Entity::crystal)
				|| (entityBehindBox == Entity::key))
			{
				// Bye bye, Crystal
				if (entityBehindBox == Entity::crystal)
					--game_info::CrystalScoreONLVL;

				// Remove box (Пока что так)
				Object* boxObject = objectsMap[y][x];
				Object* boxObject = objectsMap[y + heroDirectoinY][x + heroDirectionX];

				// 	Set box
				levelMap[y + heroDirectoinY][x + heroDirectionX] = Box;

				canMove = true;
			}

			// Logic box for Mines
			if (levelMap[y + heroDirectoinY][x + heroDirectionX] == Mine)
			{
				RestartLevel();
			}
			break;
		}

		// Door
		case Entity::door:
		{
			if (game_info::hero->CheckKey())
			{
				game_info::hero->TakeKey();
				game_info::KeyScoreONLVL--;

				canMove = true;
				break;
			}
		}

		// Level Door
		case Entity::levelDoor:
		{
			if (game_info::hero->CheckLvlkey())
			{
				game_info::hero->TakeLvlKey();

				canMove = true;
				break;
			}
		}

	}

	if (canMove)
	{
		// Remove Hero and set Empty
		levelMap[heroRow][heroColumn] = ' ';

		// Set Hero position
		heroRow = y;
		heroColumn = x;

		// Set Hero
		levelMap[heroRow][heroColumn] = Hero;

		// Reveal Fog of war
		RevealFogOfWar(heroRow, heroColumn);
	}
}

void Move()
{
	unsigned char inputChar = _getch();
	inputChar = tolower(inputChar);

	Coord heroCoord = game_info::hero->GetCoord();

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
		Inventory heroInventory = game_info::hero->GetInventory();
		// Next LVL
		case '2':
		{
			game_info::CrystalScoreONLVL     = 0;
			game_info::CrystalScoreCollected = 0;
			heroInventory.key_count = 0;
			game_info::level++;

			Initialise();
			break;
		}
		// Back LVL
		case '1':
		{
			game_info::CrystalScoreONLVL = 0;
			game_info::CrystalScoreCollected = 0;
			heroInventory.key_count = 0;
			game_info::level--;

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
		game_info::level++;
		isGameActive = true;
	}
	while (game_info::level != 6);

	Shutdown();
}
