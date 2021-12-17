#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <Windows.h>
#include "../consoleColor/colors.h"


struct ConsoleSymbolData;


class RenderSystem
{
private:
	static const int _screenY = 21;
	static const int _screenX = 40;

	ConsoleSymbolData m_backBuffer[_screenY][_screenX];
	ConsoleSymbolData m_screenBuffer[_screenY][_screenX];

public:
	RenderSystem();

	void Initialize();
	void Clear();
	void DrawChar(int y, int x, char symbol, ccolors::Color symbolColor, ccolors::Color backgroundColor);
	void DrawText(int y, int x, char* text, ccolors::Color symbolColor, ccolors::Color backgroundColor);
	void Render();

private:
	bool CompareBuffers(const ConsoleSymbolData* buf_1, const ConsoleSymbolData* buf_2) const;
};


struct ConsoleSymbolData
{
	char symbol;
	ccolors::Color symbolColor;
	ccolors::Color backgroundColor;
};

#endif // !RENDERSYSTEM_H