#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H

#include "colors.h"

namespace ccolors
{
	// Функции для консоли
	void SetDefault();			// Установка серого текста и чёрного фона
	void FullClear();			// Полная очистка и установка стандартных настроек
	void SetCursor(int Y, int X);// Установка позиции курсора
	void HideCursor();			// Скрыть курсор
	void ShowCursor();			// Отобразить курсор
	/*--------------------------***---------------------------------------------*/
	// Работа непосредственно с цветом и текстом
	void SetColor(Color symbolColor);											// Изменение цвета вывода
	void SetColor(Color symbolColor, Color backgroundColor);					// Изменение цвета вывода
	void ShowText(const char* str, Color symbolColor);							// Вывод текста
	void ShowText(const char* str, Color symbolColor, Color backgroundColor);	// Вывод текста
	/*--------------------------**----------------------------------------------*/
	// Быстрые решения
	void SayOk();				// Вывести зелёное "Ok!"
	void SayErr();				// Вывести красное "Error!"
	/*--------------------------**----------------------------------------------*/
	// Тестовые функции
	void TestColor();			// Тест цветов
}

#endif // !CONSOLE_COLOR_H
