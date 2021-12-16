#pragma once

#include <Windows.h>
#include "ConsoleColor.h"


const int screenRows = 25;
const int screenColumns = 80;


struct ConsoleSymbolData
{
	char symbol;
	CColor symbolColor;
	CColor backgroundColor;
};


class RenderSystem
{
private:
	HANDLE m_consoleHandle;
	ConsoleSymbolData m_backBuffer[screenRows][screenColumns];
	ConsoleSymbolData m_screenBuffer[screenRows][screenColumns];

private:
	void setConsoleCursor(int r, int c);
	void setConsoleColor(CColor symbolColor, CColor backgroundColor);

public:
	RenderSystem();

	void initialize();
	void clear();
	void drawChar(int r, int c, char symbol, CColor symbolColor, CColor backgroundColor);
	void drawText(int r, int c, char* text, CColor symbolColor, CColor backgroundColor);
	void flush();
};

