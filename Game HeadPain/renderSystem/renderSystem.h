#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <Windows.h>
#include "../colors.h"
#include "../RenderObject.h"

// Feature of the system: 
// 1) If the object has a black background, it is not rendered(= transparent)

class RenderSystem
{
private:
	static const int _screenY = 21 + 10; //temp!!!!!!!!!!!!!!!!!!!!!!!!!
	static const int _screenX = 40 + 25; //temp!!!!!!!!!!!!!!!!!!!!!!!!!

	RenderObject _backBuffer[_screenY][_screenX];
	RenderObject _screenBuffer[_screenY][_screenX];

	HANDLE _consoleHandle;

public:
	RenderSystem();

	void Initialize();
	void Clear();
	void DrawChar(int y, int x, const RenderObject& object);
	void DrawFrontChar(int y, int x, const RenderObject& object);
	void DrawBackground(int y, int x, Color backgroundColor);
	void SendText(int y, int x, const char* text, Color symbolColor = Color::gray, Color backgroundColor = Color::black);
	void Render();

private:
	bool CompareBuffers(const RenderObject* buf_1, const RenderObject* buf_2) const;
	void SetCursor(int Y, int X);
	void HideCursor();
	void ShowCursor();
	void SetColor(Color symbolColor, Color backgroundColor);
	void SetColor(Color symbolColor);
	void SetDefault();
};

#endif // !RENDERSYSTEM_H