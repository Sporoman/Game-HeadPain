#ifndef TEXT_WORK_H
#define TEXT_WORK_H

#include "consoleColor.h"

namespace ccolor
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

#endif // !TEXT_WORK_H
