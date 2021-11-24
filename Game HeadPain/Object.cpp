#include "Object.h"

int Object::_countObjects = 0;

Object::Object(unsigned char mapSym, unsigned char renSym, ccolor::Color colSym, Coord coord)
{
	this->_coord        = coord;
	this->_mapSymbol    = mapSym;
	this->_renderSymbol = renSym;
	this->_colorSymbol  = colSym;

	_id = _countObjects;
	++_countObjects;
}

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
	// Äëÿ x
	if (coord.x < 0)
		_coord.x = 0;
	else
		_coord.x = coord.x;

	// Äëÿ y
	if (coord.y < 0)
		_coord.y = 0;
	else
		_coord.y = coord.y;
}

int Object::GetObjectsCount()
{
	return _countObjects;
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
