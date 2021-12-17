#include "renderSystem.h"

#include "..//consoleColor/console_colors.h"
#include <cstdio>


RenderSystem::RenderSystem()
{
	for (int y = 0; y < _screenY; y++)
		for (int x = 0; x < _screenX; x++)
		{
			m_backBuffer[y][x].symbol          = 0;
			m_backBuffer[y][x].symbolColor     = ccolors::Color::gray;
			m_backBuffer[y][x].backgroundColor = ccolors::Color::black;

			m_screenBuffer[y][x] = m_backBuffer[y][x];
		}
}


void RenderSystem::Initialize()
{
	// Get console handle
	//m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Hide console cursor
	ccolors::HideCursor();
	//CONSOLE_CURSOR_INFO cursorInfo;
	//cursorInfo.dwSize = 1;
	//cursorInfo.bVisible = 0;
	///SetConsoleCursorInfo(m_consoleHandle, &cursorInfo);
}

void RenderSystem::Clear()
{
	for (int r = 0; r < _screenY; r++)
		for (int c = 0; c < _screenX; c++)
		{
			m_backBuffer[r][c].symbol          = 0;
			m_backBuffer[r][c].symbolColor     = ccolors::Color::black;
			m_backBuffer[r][c].backgroundColor = ccolors::Color::black;
		}
}

void RenderSystem::DrawChar(int y, int x, char symbol, ccolors::Color symbolColor, ccolors::Color backgroundColor)
{
	if (y < 0 || x < 0 || y >= _screenY || x >= _screenX)
		return;

	m_backBuffer[y][x].symbol          = symbol;
	m_backBuffer[y][x].symbolColor     = symbolColor;
	m_backBuffer[y][x].backgroundColor = backgroundColor;
}

void RenderSystem::DrawText(int y, int x, char* text, ccolors::Color symbolColor, ccolors::Color backgroundColor)
{
	int  next_x = x;
	char symbol = *text;

	while (symbol != 0)
	{
		DrawChar(y, next_x, symbol, symbolColor, backgroundColor);

		++text;
		++next_x;
		symbol = *text;
	}
}

void RenderSystem::Render()
{
	bool screenBufferModified = false;

	for (int y = 0; y < _screenY; y++)
	{
		for (int x = 0; x < _screenX; x++)
		{
			if (CompareBuffers(&m_backBuffer[y][x], &m_screenBuffer[y][x]))
			{
				// Copy symbol data from back to screen buffer
				m_screenBuffer[y][x] = m_backBuffer[y][x];

				// Draw symbol in (y,x) position
				ccolors::SetCursor(y, x);
				ccolors::SetColor(m_screenBuffer[y][x].symbolColor, m_screenBuffer[y][x].backgroundColor);
				printf("%c", m_screenBuffer[y][x]);
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				screenBufferModified = true;
			}
		}
	}

	// Return console cursor to (0,0)
	if (screenBufferModified)
		ccolors::SetCursor(0, 0);
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
