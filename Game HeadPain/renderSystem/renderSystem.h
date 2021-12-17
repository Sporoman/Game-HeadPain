#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <Windows.h>
#include "../colors.h"


struct ConsoleSymbolData
{
	char symbol;
	Color symbolColor;
	Color backgroundColor;
};


class RenderSystem
{
private:
	static const int _screenY = 21 + 10; //temp!!!!!!!!!!!!!!!!!!!!!!!!!
	static const int _screenX = 40 + 21; //temp!!!!!!!!!!!!!!!!!!!!!!!!!

	ConsoleSymbolData _backBuffer[_screenY][_screenX];
	ConsoleSymbolData _screenBuffer[_screenY][_screenX];

	HANDLE _consoleHandle;

public:
	RenderSystem();

	void Initialize();
	void Clear();
	void DrawChar(int y, int x, char symbol, Color symbolColor = Color::gray, Color backgroundColor = Color::black);
	void SendText(int y, int x, const char* text, Color symbolColor = Color::gray, Color backgroundColor = Color::black);
	void Render();

private:
	bool CompareBuffers(const ConsoleSymbolData* buf_1, const ConsoleSymbolData* buf_2) const;
	void SetCursor(int Y, int X);
	void HideCursor();
	void ShowCursor();
	void SetColor(Color symbolColor, Color backgroundColor);
	void SetColor(Color symbolColor);
	void SetDefault();
};


//struct ConsoleSymbolData
//{
//	char symbol;
//	Color symbolColor;
//	Color backgroundColor;
//};

#endif // !RENDERSYSTEM_H