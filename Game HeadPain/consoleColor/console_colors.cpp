#include <Windows.h>
#include <iostream>

#include "console_colors.h"


// Получаем дискриптор консоли	
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

// Установка серого текста и чёрного фона
void ccolors::SetDefault()
{
	int consoleColor = static_cast<int>(Color::gray) | static_cast<int>(Color::black) << 4;
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// Полная очистка консоли и сброс её настроек
void ccolors::FullClear()
{
	ccolors::SetDefault();
	system("cls");
}

// Установка курсора консоли
void ccolors::SetCursor(int Y, int X)
{
	COORD cursorCoord;
	cursorCoord.X = X;
	cursorCoord.Y = Y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

// Скрыть курсор
void ccolors::HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize   = 1;	// От 1 до 100
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// Отобразить курсор
void ccolors::ShowCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = true;
	cursorInfo.dwSize  = 25;	// От 1 до 100
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// Изменение цвета вывода
void ccolors::SetColor(Color symbolColor, Color backgroundColor)
{
	int consoleColor = static_cast<int>(symbolColor) | static_cast<int>(backgroundColor) << 4;
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// Изменение цвета вывода
void ccolors::SetColor(Color symbolColor)
{
	int consoleColor = static_cast<int>(symbolColor);
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// Вывод текста
void ccolors::ShowText(const char* str, Color symbolColor, Color backgroundColor)
{
	ccolors::SetColor(symbolColor, backgroundColor);
	std::cout << str;
	ccolors::SetDefault();
}

// Вывод текста
void ccolors::ShowText(const char* str, Color symbolColor)
{
	ccolors::SetColor(symbolColor);
	std::cout << str;
	ccolors::SetDefault();
}



void ccolors::SayOk()
{
	ccolors::SetColor(Color::green);
	std::cout << "ok" << std::endl;
	ccolors::SetDefault();
}

void ccolors::SayErr()
{
	ccolors::SetColor(Color::red);
	std::cout << "error" << std::endl;
	ccolors::SetDefault();
}


// Тест цветов
void ccolors::TestColor()
{
	std::cout << "\t";							//
	for (int i = 0; i < 16; i++)				//		ТЕСТ!
	{											//		 для
		Color color = static_cast<Color>(i);	//	 определения
		ccolors::SetColor(color);				//		цвета
		std::cout << "z ";						//
	}
	std::cout << "\t";
}
