#include <Windows.h>
#include <iostream>

#include "text_work.h"


// �������� ���������� �������	
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

// ��������� ������ ������ � ������� ����
void ccolor::SetDefault()
{
	int consoleColor = static_cast<int>(Color::gray) | static_cast<int>(Color::black) << 4;
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// ������ ������� ������� � ����� � ��������
void ccolor::FullClear()
{
	ccolor::SetDefault();
	system("cls");
}

// ��������� ������� �������
void ccolor::SetCursor(int Y, int X)
{
	COORD cursorCoord;
	cursorCoord.X = X;
	cursorCoord.Y = Y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

// ������ ������
void ccolor::HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize   = 1;	// �� 1 �� 100
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// ���������� ������
void ccolor::ShowCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = true;
	cursorInfo.dwSize  = 25;	// �� 1 �� 100
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// ��������� ����� ������
void ccolor::SetColor(Color symbolColor, Color backgroundColor)
{
	int consoleColor = static_cast<int>(symbolColor) | static_cast<int>(backgroundColor) << 4;
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// ��������� ����� ������
void ccolor::SetColor(Color symbolColor)
{
	int consoleColor = static_cast<int>(symbolColor);
	SetConsoleTextAttribute(consoleHandle, consoleColor);
}

// ����� ������
void ccolor::ShowText(const char* str, Color symbolColor, Color backgroundColor)
{
	ccolor::SetColor(symbolColor, backgroundColor);
	std::cout << str;
	ccolor::SetDefault();
}

// ����� ������
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


// ���� ������
void ccolor::TestColor()
{
	std::cout << "\t";							//
	for (int i = 0; i < 16; i++)				//		����!
	{											//		 ���
		Color color = static_cast<Color>(i);	//	 �����������
		ccolor::SetColor(color);			//		�����
		std::cout << "z ";						//
	}
	std::cout << "\t";
}
