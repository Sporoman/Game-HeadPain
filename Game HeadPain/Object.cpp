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
{}

void Object::SetCoord(int x, int y)
{
	_coord.x = x;
	_coord.y = y;
}

void Object::SetCoord(Coord coord)
{
	_coord.x = coord.x;
	_coord.y = coord.y;
}

int Object::GetObjectsCount()
{
	return _countObjects;
}

void Object::MoveOnUp()
{

}

void Object::MoveOnLeft()
{

}

void Object::MoveOnRight()
{

}

void Object::MoveOnDown()
{

}
