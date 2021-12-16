#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H

#include "colors.h"

namespace ccolors
{
	// ������� ��� �������
	void SetDefault();			// ��������� ������ ������ � ������� ����
	void FullClear();			// ������ ������� � ��������� ����������� ��������
	void SetCursor(int Y, int X);// ��������� ������� �������
	void HideCursor();			// ������ ������
	void ShowCursor();			// ���������� ������
	/*--------------------------***---------------------------------------------*/
	// ������ ��������������� � ������ � �������
	void SetColor(Color symbolColor);											// ��������� ����� ������
	void SetColor(Color symbolColor, Color backgroundColor);					// ��������� ����� ������
	void ShowText(const char* str, Color symbolColor);							// ����� ������
	void ShowText(const char* str, Color symbolColor, Color backgroundColor);	// ����� ������
	/*--------------------------**----------------------------------------------*/
	// ������� �������
	void SayOk();				// ������� ������ "Ok!"
	void SayErr();				// ������� ������� "Error!"
	/*--------------------------**----------------------------------------------*/
	// �������� �������
	void TestColor();			// ���� ������
}

#endif // !CONSOLE_COLOR_H
