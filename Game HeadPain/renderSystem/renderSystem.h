#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <Windows.h>
#include "../consoleColor/colors.h"


struct ConsoleSymbolData
{
	char symbol;
	ccolors::Color symbolColor;
	ccolors::Color backgroundColor;
};


class RenderSystem
{
private:
	static const int _screenY = 21 + 10; //temp!!!!!!!!!!!!!!!!!!!!!!!!!
	static const int _screenX = 40 + 20; //temp!!!!!!!!!!!!!!!!!!!!!!!!!

	ConsoleSymbolData _backBuffer[_screenY][_screenX];
	ConsoleSymbolData _screenBuffer[_screenY][_screenX];

	HANDLE _consoleHandle;

public:
	RenderSystem();

	void Initialize();
	void Clear();
	void DrawChar(int y, int x, char symbol, ccolors::Color symbolColor, ccolors::Color backgroundColor);
	void DrawTextW(int y, int x, const char* text, ccolors::Color symbolColor, ccolors::Color backgroundColor);
	void Render();

private:
	bool CompareBuffers(const ConsoleSymbolData* buf_1, const ConsoleSymbolData* buf_2) const;
	void SetCursor(int Y, int X);
	void HideCursor();
	void ShowCursor();
	void SetColor(ccolors::Color symbolColor, ccolors::Color backgroundColor);
	void SetColor(ccolors::Color symbolColor);
	void SetDefault();
};


//struct ConsoleSymbolData
//{
//	char symbol;
//	ccolors::Color symbolColor;
//	ccolors::Color backgroundColor;
//};

#endif // !RENDERSYSTEM_H