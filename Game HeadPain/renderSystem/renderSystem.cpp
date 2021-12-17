#include "renderSystem.h"

#include "../colors.h"
#include <cstdio>


RenderSystem::RenderSystem()
{
	for (int y = 0; y < _screenY; y++)
		for (int x = 0; x < _screenX; x++)
		{
			_backBuffer[y][x].symbol          = 0;
			_backBuffer[y][x].symbolColor     = Color::gray;
			_backBuffer[y][x].backgroundColor = Color::black;

			_screenBuffer[y][x] = _backBuffer[y][x];
		}
}


void RenderSystem::Initialize()
{
	// Get console handle
	_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Hide console cursor
	HideCursor();
}

void RenderSystem::Clear()
{
	for (int r = 0; r < _screenY; r++)
		for (int c = 0; c < _screenX; c++)
		{
			_backBuffer[r][c].symbol          = 0;
			_backBuffer[r][c].symbolColor     = Color::black;
			_backBuffer[r][c].backgroundColor = Color::black;
		}
}

void RenderSystem::DrawChar(int y, int x, char symbol, Color symbolColor, Color backgroundColor)
{
	if (y < 0 || x < 0 || y >= _screenY || x >= _screenX)
		return;

	_backBuffer[y][x].symbol          = symbol;
	_backBuffer[y][x].symbolColor     = symbolColor;
	_backBuffer[y][x].backgroundColor = backgroundColor;
}

void RenderSystem::SendText(int y, int x, const char* text, Color symbolColor, Color backgroundColor)
{
	int  next_x = x;
	char symbol = *text;

	while (symbol != 0)
	{
		DrawChar(y, next_x, symbol, symbolColor, backgroundColor);

		++text;
		++next_x;
		symbol = *text;

		if (next_x >= _screenX)
			return;
	}
}

void RenderSystem::Render()
{
	bool screenBufferModified = false;

	for (int y = 0; y < _screenY; y++)
	{
		for (int x = 0; x < _screenX; x++)
		{
			if (CompareBuffers(&_backBuffer[y][x], &_screenBuffer[y][x]))
			{
				// Copy symbol data from back to screen buffer
				_screenBuffer[y][x] = _backBuffer[y][x];

				// Draw symbol in (y,x) position
				SetCursor(y, x);
				SetColor(_screenBuffer[y][x].symbolColor, _screenBuffer[y][x].backgroundColor);
				printf("%c", _screenBuffer[y][x].symbol);

				screenBufferModified = true;
			}
		}
	}

	// Return console cursor to (0,0)
	//if (screenBufferModified)
	//	SetCursor(0, 0);
}

bool RenderSystem::CompareBuffers(const ConsoleSymbolData* buf_1, const ConsoleSymbolData* buf_2) const
{
	if (  (buf_1->symbol != buf_2->symbol)
	   || (buf_1->symbolColor != buf_2->symbolColor)
	   || (buf_1->backgroundColor != buf_2->backgroundColor)
	   )
		return true;
	else
		return false;
}

// Установка курсора консоли
void RenderSystem::SetCursor(int Y, int X)
{
	COORD cursorCoord;
	cursorCoord.X = X;
	cursorCoord.Y = Y;
	SetConsoleCursorPosition(_consoleHandle, cursorCoord);
}

// Скрыть курсор
void RenderSystem::HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 1;	// От 1 до 100
	SetConsoleCursorInfo(_consoleHandle, &cursorInfo);
}

// Отобразить курсор
void RenderSystem::ShowCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = true;
	cursorInfo.dwSize = 25;	// От 1 до 100
	SetConsoleCursorInfo(_consoleHandle, &cursorInfo);
}

// Изменение цвета вывода
void RenderSystem::SetColor(Color symbolColor, Color backgroundColor)
{
	int consoleColor = static_cast<int>(symbolColor) | static_cast<int>(backgroundColor) << 4;
	SetConsoleTextAttribute(_consoleHandle, consoleColor);
}

// Изменение цвета вывода
void RenderSystem::SetColor(Color symbolColor)
{
	int consoleColor = static_cast<int>(symbolColor);
	SetConsoleTextAttribute(_consoleHandle, consoleColor);
}

// Установка серого текста и чёрного фона
void RenderSystem::SetDefault()
{
	int consoleColor = static_cast<int>(Color::gray) | static_cast<int>(Color::black) << 4;
	SetConsoleTextAttribute(_consoleHandle, consoleColor);
}