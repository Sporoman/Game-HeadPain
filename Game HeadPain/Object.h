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
	Coord _coord                {0,0};					// Coords
	unsigned char _mapSymbol    = '?';					// Symbol on the physical map (before render)
	unsigned char _renderSymbol = '?';					// Symbol on the visual map (after render)
	ccolor::Color _colorSymbol  = ccolor::Color::red;	// Symbol color

public:
	Object(unsigned char mapSym, unsigned char renSym, ccolor::Color colSym, Coord coord);
	~Object();

	virtual void MoveOn(DirMove dir);

	virtual void SetCoord(int x, int y);
	virtual void SetCoord(Coord coord);

	static int GetObjectsCount();

private:
	void MoveOnUp();
	void MoveOnLeft();
	void MoveOnRight();
	void MoveOnDown();
};

#endif // COORD_H