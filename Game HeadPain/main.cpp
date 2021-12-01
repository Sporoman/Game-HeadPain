// Library
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "Levels.h"
#include "consoleColor//text_work.h"

// This file is a temporary solution

// Logic
bool isGameActive = true;
unsigned char levelData[game_info::y_size_lvl][game_info::x_size_lvl];
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
}

void RevealFogOfWar(int y, int x)
{
	if (hard == true)
	{
		for (int r = y - 3; r <= y + 3; r++)
			for (int c = x - 3; c <= x + 3; c++)
				fogOfWarB[r][c] = false;
	}
}

void Initialise()
{
	// Load Level
	for (int y = 0; y < game_info::y_size_lvl; y++)
	{
		for (int x = 0; x < game_info::x_size_lvl; x++)
		{
			if (hard == true)
				fogOfWarB[y][x] = true;
			else
				fogOfWarB[y][x] = false;

			unsigned char symbol = game_info::levelsData[game_info::level][y][x];//s
			levelData[y][x] = symbol;

			if (levelData[y][x] == Hero)
			{
				heroRow = y;
				heroColumn = x;
			}

			switch (symbol)
			{
				case Crystal: CrystalScoreONLVL++; break;
			}
		}
	}

	RevealFogOfWar(heroRow, heroColumn);
}

void Render()
{
	// Cursor to (0,0)
	ccolor::SetCursor(0, 0);
	ccolor::HideCursor();

	printf("\n\t");
	for (int r = 0; r < game_info::y_size_lvl; r++)
	{
		for (int c = 0; c < game_info::x_size_lvl; c++)
		{
			if (fogOfWarB[r][c] == false)
			{
				unsigned char symbol = levelData[r][c];
				unsigned char renderSymbol = GetRenderCellSymbol(symbol);

				ccolor::Color cellColor = GetRenderCellSymbolColor(symbol);
				ccolor::SetColor(cellColor);

				printf("%c", renderSymbol);
			}
			else
			{
				ccolor::SetColor(ccolor::Color::gray);
				printf("%c", game_info::mapSymbol_fogOfWar);
			}
		}

		if (r == 2)
		{
			ccolor::SetColor(ccolor::Color::gray);
			printf("   Level %i  ", game_info::level + 1);
		}

		if (r == 3)
		{
			ccolor::SetColor(ccolor::Color::blue);
			printf("   Level Key ");
			ccolor::SetColor(ccolor::Color::gray);
			if (LevelKeyScore == 1)
				printf(": yeap  ");
			if (LevelKeyScore == 0)
				printf(": nope  ");
		}

		if (r == 4)
		{
			ccolor::SetColor(ccolor::Color::cyan);
			printf("   Key ");
			ccolor::SetColor(ccolor::Color::gray);
			printf(": %i  ", KeyScore);
		}

		if (r == 5)
		{
			ccolor::SetColor(ccolor::Color::darkMagenta);
			printf("   Crystal");
			ccolor::SetColor(ccolor::Color::gray);
			printf(": %i  \t", CrystalScore);
		}

		if (r == 6)
		{
			ccolor::SetColor(ccolor::Color::darkMagenta);
			printf("   Crystal");
			ccolor::SetColor(ccolor::Color::gray);
			printf(" on level: %i   ", CrystalScoreONLVL);
		}

		if (r == 9) //X coord hero for test
		{
			ccolor::SetColor(ccolor::Color::gray);
			printf("   X coord hero: %i   ", heroColumn);
		}
		if (r == 10) //Y coord hero for test
		{
			ccolor::SetColor(ccolor::Color::gray);
			printf("   Y coord hero: %i   ", heroRow);
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
	printf(" to restart.");
}

void RestartLevel()
{
	CrystalScore -= CrystalScoreCollected;
	CrystalScoreCollected = 0;
	CrystalScoreONLVL = 0;
	KeyScore -= KeyScoreLVL;
	KeyScoreLVL = 0;
	Initialise();
}

void MoveHeroTo(int row, int column)
{
	unsigned char destinationCell = levelData[row][column];
	bool canMove = false;

	switch (destinationCell)
	{
		// Void
		case Void:
		{
			canMove = true;
			break;
		}

		// Crystal
		case Crystal:
		{
			CrystalScore++;
			CrystalScoreCollected++;
			CrystalScoreONLVL--;
			canMove = true;
			break;
		}

		// Key
		case Key:
		{
			KeyScore++;
			KeyScoreLVL++;
			canMove = true;
			break;
		}
		case LevelKey:
		{
			LevelKeyScore++;
			canMove = true;
			break;
		}

		// Mine
		case Mine:
		{
			RestartLevel();
			break;
		}

		// Exit
		case Exit:
		{
			CrystalScoreONLVL = 0;
			CrystalScoreCollected = 0;
			KeyScoreLVL = 0;
			LevelKeyScore = 0;
			isGameActive = false;
			break;
		}

		// Box
		case Box:
		{
			// Hero move direction
			int heroDirectoinR = row - heroRow;
			int heroDirectionC = column - heroColumn;


			// Check space behind the box
			if ((levelData[row + heroDirectoinR][column + heroDirectionC] == ' ') or
				(levelData[row + heroDirectoinR][column + heroDirectionC] == Crystal) or
				(levelData[row + heroDirectoinR][column + heroDirectionC] == Key))
			{
				canMove = true;

				if (levelData[row + heroDirectoinR][column + heroDirectionC] == Crystal)
					CrystalScoreONLVL--;

				// Remove box
				levelData[row][column] = ' ';

				// 	Set box
				levelData[row + heroDirectoinR][column + heroDirectionC] = Box;
			}

			// Logic box for Mines
			if (levelData[row + heroDirectoinR][column + heroDirectionC] == Mine)
			{
				RestartLevel();
			}
			break;
		}

		// Door
		case Door:
		{
			if (KeyScore > 0)
			{
				canMove = true;
				KeyScore--;
				KeyScoreLVL--;
				break;
			}
		}

		// Level Door
		case LevelDoor:
		{
			if (LevelKeyScore > 0)
			{
				canMove = true;
				LevelKeyScore--;
				break;
			}
		}

	}

	if (canMove)
	{
		// Remove Hero
		levelData[heroRow][heroColumn] = ' ';

		// Set Hero position
		heroRow = row;
		heroColumn = column;

		// Set Hero
		levelData[heroRow][heroColumn] = Hero;

		// Reveal Fog of war
		RevealFogOfWar(heroRow, heroColumn);
	}
}

void Move()
{
	unsigned char inputChar = _getch();
	inputChar = tolower(inputChar);

	switch (inputChar)
	{
		// Up
		case 'w': case 230: case 150:
		{
			MoveHeroTo(heroRow - 1, heroColumn);
			break;
		}

		// Down
		case 's': case 235: case 155:
		{
			MoveHeroTo(heroRow + 1, heroColumn);
			break;
		}

		// Left
		case 'a': case 228: case 148:
		{
			MoveHeroTo(heroRow, heroColumn - 1);
			break;
		}

		// Right
		case 'd': case 162: case 130:
		{
			MoveHeroTo(heroRow, heroColumn + 1);
			break;
		}

		// Restart level
		case 'r': case 170: case 138:
		{
			RestartLevel();
			break;
		}
		// Next LVL
		case '2':
		{
			CrystalScoreONLVL = 0;
			CrystalScoreCollected = 0;
			KeyScoreLVL = 0;
			level++;
			Initialise();
			break;
		}
		// Back LVL
		case '1':
		{
			CrystalScoreONLVL = 0;
			CrystalScoreCollected = 0;
			KeyScoreLVL = 0;
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
