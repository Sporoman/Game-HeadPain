#include "Object.h"

int Object::__idObjects    = 0;
int Object::__countObjects = 0;

Object::Object(unsigned char mapSymbol, Coord coord)
	: _mapSymbol(mapSymbol), _coord(coord)
{
	// Object id
	_id = __idObjects;
	++__idObjects;

	// Plus the count of objects
	++__countObjects;

	// Initializing the object
	//_mapSymbol;
	_entity		  = GetInitializeEntity(_mapSymbol);
	_renderSymbol = GetInitializeRenderSymbol(_entity);
	_colorSymbol  = GetInitializeColorSymbol(_entity);
}

Object::Object(unsigned char mapSymbol) : Object(mapSymbol, Coord{ 0,0 })
{}

Object::~Object()
{
	// Minus the count of objects
	--__countObjects;
}

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

unsigned char Object::GetRenderSymbol()
{
	return _renderSymbol;
}

ccolor::Color Object::GetColor()
{
	return _colorSymbol;
}

Coord Object::GetCoord()
{
	return _coord;
}

Entity Object::GetEntity()
{
	return _entity;
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

Entity Object::GetInitializeEntity(unsigned char mapSymbol)
{
	switch (mapSymbol)
	{
		case 176:	return Entity::fogOfWar;
		case ' ':	return Entity::empty;
		case 'H':	return Entity::hero;
		case '#':	return Entity::wall;
		case 'D':	return Entity::door;
		case '[':	return Entity::levelDoor;
		case 'K':	return Entity::key;
		case ']':	return Entity::levelKey;
		case 'B':	return Entity::box;
		case 'E':	return Entity::exitDoor;
		case 'C':	return Entity::crystal;
		case 'M':	return Entity::mine;

		default: return Entity::error;
	}
}

unsigned char Object::GetInitializeRenderSymbol(Entity entity)
{
	switch (entity)
	{
		case Entity::empty:			return ' ';
		case Entity::hero:			return 2;
		case Entity::wall:			return 177;
		case Entity::door:			return 219;
		case Entity::levelDoor:		return 219;
		case Entity::key:			return 21;
		case Entity::levelKey:		return 21;
		case Entity::box:			return 254;
		case Entity::exitDoor:		return 176;
		case Entity::crystal:		return 4;
		case Entity::mine:			return 15;
		case Entity::fogOfWar:		return 176;

		case Entity::error:
		default: return '?';
	}
}

ccolor::Color Object::GetInitializeColorSymbol(Entity entity)
{
	switch (entity)
	{
		case Entity::empty:			return ccolor::Color::black;
		case Entity::hero:			return ccolor::Color::green;
		case Entity::wall:			return ccolor::Color::white;
		case Entity::door:			return ccolor::Color::yellow;
		case Entity::levelDoor:		return ccolor::Color::blue;
		case Entity::key:			return ccolor::Color::cyan;
		case Entity::levelKey:		return ccolor::Color::blue;
		case Entity::box:			return ccolor::Color::brown;
		case Entity::exitDoor:		return ccolor::Color::magenta;
		case Entity::crystal:		return ccolor::Color::magenta;
		case Entity::mine:			return ccolor::Color::red;
		case Entity::fogOfWar:		return ccolor::Color::gray;

		case Entity::error:
		default: return ccolor::Color::red;
	}
}
