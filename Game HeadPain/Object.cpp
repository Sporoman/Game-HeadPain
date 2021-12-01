#include "Object.h"

int Object::__countObjects = 0;

Object::Object(unsigned char mapSym, unsigned char renSym, ccolor::Color colSym, Coord coord)
	: _mapSymbol(mapSym), _renderSymbol(renSym), _colorSymbol(colSym), _coord(coord)
{
	_id = __countObjects;
	++__countObjects;
}

Object::Object(unsigned char mapSym, unsigned char renSym, ccolor::Color colSym) : Object(mapSym, renSym, colSym, Coord{ 0,0 })
{}

Object::~Object()
{}

void Object::MoveOn(DirMove dir)
{
	switch (dir)
	{
		case DirMove::up:       MoveOnUp();       break;
		case DirMove::left:     MoveOnLeft();     break;
		case DirMove::down:     MoveOnDown();     break;
		case DirMove::right:    MoveOnRight();    break;

		default: break;
	}
}

void Object::SetCoord(int x, int y)
{
	Coord coord{ x,y };
	SetCoord(coord);
}

void Object::SetCoord(Coord coord)
{
	// For "x"
	if (coord.x < 0)
		_coord.x = 0;
	else
		_coord.x = coord.x;

	// For "y"
	if (coord.y < 0)
		_coord.y = 0;
	else
		_coord.y = coord.y;
}

unsigned char Object::GetMapSymbol()
{
	return _mapSymbol;
}

int Object::GetObjectsCount()
{
	return __countObjects;
}

void Object::MoveOnUp()
{
	if (_coord.y <= 0)
		_coord.y = 0;
	else
		--_coord.y;
}

void Object::MoveOnLeft()
{
	if (_coord.x <= 0)
		_coord.x = 0;
	else
		--_coord.x;
}

void Object::MoveOnRight()
{
	++_coord.x;
}

void Object::MoveOnDown()
{
	++_coord.y;
}
