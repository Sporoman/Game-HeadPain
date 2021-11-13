#include <Windows.h>
#include <iostream>

#include "text_work.h"


// Получаем дискриптор консоли	
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

// Установка серого текста и чёрного фона
void ccolor::SetDefault()
{
	int consoleColor = static_cast<int>(Color::gray) | static_cast<int>(Color::black) << 4;
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// Полная очистка консоли и сброс её настроек
void ccolor::FullClear()
{
	ccolor::SetDefault();
	system("cls");
}

// Установка курсора консоли
void ccolor::SetCursor(int Y, int X)
{
	COORD cursorCoord;
	cursorCoord.X = X;
	cursorCoord.Y = Y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

// Скрыть курсор
void ccolor::HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize   = 1;	// От 1 до 100
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// Отобразить курсор
void ccolor::ShowCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = true;
	cursorInfo.dwSize  = 25;	// От 1 до 100
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// Изменение цвета вывода
void ccolor::SetColor(Color symbolColor, Color backgroundColor)
{
	int consoleColor = static_cast<int>(symbolColor) | static_cast<int>(backgroundColor) << 4;
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// Изменение цвета вывода
void ccolor::SetColor(Color symbolColor)
{
	int consoleColor = static_cast<int>(symbolColor);
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// Вывод текста
void ccolor::ShowText(const char* str, Color symbolColor, Color backgroundColor)
{
	ccolor::SetColor(symbolColor, backgroundColor);
	std::cout << str;
	ccolor::SetDefault();
}

// Вывод текста
void ccolor::ShowText(const char* str, Color symbolColor)
{
	ccolor::SetColor(symbolColor);
	std::cout << str;
	ccolor::SetDefault();
}



void ccolor::SayOk()
{
	ccolor::SetColor(Color::green);
	std::cout << "ok" << std::endl;
	ccolor::SetDefault();
}

void ccolor::SayErr()
{
	ccolor::SetColor(Color::red);
	std::cout << "error" << std::endl;
	ccolor::SetDefault();
}


// Тест цветов
void ccolor::TestColor()
{
	std::cout << "\t";							//
	for (int i = 0; i < 16; i++)				//		ТЕСТ!
	{											//		 для
		Color color = static_cast<Color>(i);	//	 определения
		ccolor::SetColor(color);			//		цвета
		std::cout << "z ";						//
	}
	std::cout << "\t";
}
