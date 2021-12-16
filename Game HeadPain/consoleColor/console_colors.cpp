#include <Windows.h>
#include <iostream>

#include "console_colors.h"


// �������� ���������� �������	
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

// ��������� ������ ������ � ������� ����
void ccolors::SetDefault()
{
	int consoleColor = static_cast<int>(Color::gray) | static_cast<int>(Color::black) << 4;
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// ������ ������� ������� � ����� � ��������
void ccolors::FullClear()
{
	ccolors::SetDefault();
	system("cls");
}

// ��������� ������� �������
void ccolors::SetCursor(int Y, int X)
{
	COORD cursorCoord;
	cursorCoord.X = X;
	cursorCoord.Y = Y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

// ������ ������
void ccolors::HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize   = 1;	// �� 1 �� 100
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// ���������� ������
void ccolors::ShowCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = true;
	cursorInfo.dwSize  = 25;	// �� 1 �� 100
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// ��������� ����� ������
void ccolors::SetColor(Color symbolColor, Color backgroundColor)
{
	int consoleColor = static_cast<int>(symbolColor) | static_cast<int>(backgroundColor) << 4;
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// ��������� ����� ������
void ccolors::SetColor(Color symbolColor)
{
	int consoleColor = static_cast<int>(symbolColor);
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// ����� ������
void ccolors::ShowText(const char* str, Color symbolColor, Color backgroundColor)
{
	ccolors::SetColor(symbolColor, backgroundColor);
	std::cout << str;
	ccolors::SetDefault();
}

// ����� ������
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


// ���� ������
void ccolors::TestColor()
{
	std::cout << "\t";							//
	for (int i = 0; i < 16; i++)				//		����!
	{											//		 ���
		Color color = static_cast<Color>(i);	//	 �����������
		ccolors::SetColor(color);				//		�����
		std::cout << "z ";						//
	}
	std::cout << "\t";
}
