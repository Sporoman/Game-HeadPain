#ifndef COOORD_H
#define COORD_H

#include "Coord.h"
#include "consoleColor//ConsoleColor.h"

enum class DirMove
{
	up    = 0,
	left  = 1,
	down  = 2, 
	right = 3,
};

class Object
{
private:
	static int _countObjects;

	int _id;
	Coord _coord                {0,0};					// Координаты
	unsigned char _mapSymbol    = '?';					// Символ на карте (до рендеринга)
	unsigned char _renderSymbol = '?';					// Символ отображения (рендеринг)
	ccolor::Color _colorSymbol  = ccolor::Color::red;	// Цвет символа

public:
	Object(unsigned char mapSym, unsigned char renSym, ccolor::Color colSym, Coord coord);
	~Object();

	virtual void MoveOn(DirMove dir);		// Движение

	virtual void SetCoord(int x, int y);	// Задать координаты
	virtual void SetCoord(Coord coord);		// Задать координаты

	static int GetObjectsCount();	// Получить количество объектов

private:
	void MoveOnUp();
	void MoveOnLeft();
	void MoveOnRight();
	void MoveOnDown();
};

#endif // COORD_H