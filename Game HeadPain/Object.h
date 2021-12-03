#ifndef OBJECT_H
#define OBJECT_H

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
	static int __countObjects;

	int _id;
	Coord _coord;	                      				// Coords
	unsigned char _mapSymbol    = '?';					// Symbol on the physical map (before render)
	unsigned char _renderSymbol = '?';					// Symbol on the visual map (after render)
	ccolor::Color _colorSymbol  = ccolor::Color::red;	// Symbol color

public:
	Object(unsigned char mapSym, unsigned char renSym, ccolor::Color colSym, Coord coord);
	Object(unsigned char mapSym, unsigned char renSym, ccolor::Color colSym);
	~Object();

	static int GetObjectsCount();

	virtual void MoveOn(DirMove dir);
	virtual void SetCoord(int x, int y);
	virtual void SetCoord(Coord coord);

	virtual Coord GetCoord();
	virtual unsigned char GetMapSymbol();
	

private:
	void MoveOnUp();
	void MoveOnLeft();
	void MoveOnRight();
	void MoveOnDown();
};

#endif // OBJECT_H