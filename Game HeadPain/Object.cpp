#include "Object.h"

int Object::__idObjects    = 0;
int Object::__countObjects = 0;

Object::Object(unsigned char symbol) : Object(symbol, Coord{ 0,0 })
{}

Object::Object(unsigned char symbol, Coord coord) : Object(GetInitEntity(symbol), coord)
{}

Object::Object(Entity entity, Coord coord) : _entity(entity), _coord(coord)
{
	// Object id
	_id = __idObjects;
	__idObjects++;

	// Plus the count of objects
	__countObjects++;

	// Initializing the object
	_mapSymbol = GetInitMapSymbol(_entity);

	// Initializing the render object
	_renderObj.symbol      = GetInitRenderSymbol(_entity);
	_renderObj.symbolColor = GetInitColorSymbol(_entity);
	_renderObj.bkgColor    = GetInitColorBkg(_entity);
}

Object::Object(Entity entity) : Object(entity, Coord{ 0,0 })
{}

Object::~Object()
{
	// Minus the count of objects
	__countObjects--;
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
	if (coord.x < 0)
		_coord.x = 0;
	else
		_coord.x = coord.x;

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
	return _renderObj.symbol;
}

Color Object::GetColorSymbol()
{
	return _renderObj.symbolColor;
}

Color Object::GetColorBackground()
{
	return _renderObj.bkgColor;
}

const RenderObject& Object::GetRenderObject()
{
	return _renderObj;
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
		_coord.y--;
}

void Object::MoveOnLeft()
{
	if (_coord.x <= 0)
		_coord.x = 0;
	else
		_coord.x--;
}

void Object::MoveOnRight()
{
	_coord.x++;
}

void Object::MoveOnDown()
{
	_coord.y++;
}

Entity Object::GetInitEntity(unsigned char symbol)
{
	switch (symbol)
	{
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
		case 176:	return Entity::fogOfWar;
		case '3':	return Entity::hearts;

		default: return Entity::error;
	}
}

unsigned char Object::GetInitMapSymbol(Entity entity)
{
	switch (entity)
	{
		case Entity::empty:			return ' ';
		case Entity::hero:			return 'H';
		case Entity::wall:			return '#';
		case Entity::door:			return 'D';
		case Entity::levelDoor:		return '[';
		case Entity::key:			return 'K';
		case Entity::levelKey:		return ']';
		case Entity::box:			return 'B';
		case Entity::exitDoor:		return 'E';
		case Entity::crystal:		return 'C';
		case Entity::mine:			return 'M';
		case Entity::fogOfWar:		return 176;
		case Entity::hearts:		return '3';

		case Entity::error:
		default: return '?';
	}
}

unsigned char Object::GetInitRenderSymbol(Entity entity)
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
		case Entity::hearts:		return 3;

		case Entity::error:
		default: return '?';
	}
}

Color Object::GetInitColorSymbol(Entity entity)
{
	switch (entity)
	{
		case Entity::empty:			return Color::black;
		case Entity::hero:			return Color::green;
		case Entity::wall:			return Color::white;
		case Entity::door:			return Color::yellow;
		case Entity::levelDoor:		return Color::blue;
		case Entity::key:			return Color::yellow;
		case Entity::levelKey:		return Color::blue;
		case Entity::box:			return Color::brown;
		case Entity::exitDoor:		return Color::magenta;
		case Entity::crystal:		return Color::magenta;
		case Entity::mine:			return Color::red;
		case Entity::fogOfWar:		return Color::gray;
		case Entity::hearts:		return Color::red;

		case Entity::error:
		default: return Color::red;
	}
}

Color Object::GetInitColorBkg(Entity entity)
{
	switch (entity)
	{
		case Entity::empty:			return Color::black;
		case Entity::hero:			return Color::black;
		case Entity::wall:			return Color::black;
		case Entity::door:			return Color::black;
		case Entity::levelDoor:		return Color::black;
		case Entity::key:			return Color::black;
		case Entity::levelKey:		return Color::black;
		case Entity::box:			return Color::black;
		case Entity::exitDoor:		return Color::black;
		case Entity::crystal:		return Color::black;
		case Entity::mine:			return Color::black;
		case Entity::fogOfWar:		return Color::black;
		case Entity::hearts:		return Color::black;

		case Entity::error:
		default: return Color::darkMagenta;
	}
}

Color Object::GetInitColorFromBkgMap(unsigned char symbol)
{
	switch (symbol)
	{
		case '#': 
		case '0':    return Color::black;
		case 'B':    return Color::darkBlue;
		case 'G':    return Color::darkGreen;
		case 'C':    return Color::darkCyan;
		case 'R':    return Color::darkRed;
		case 'M':    return Color::darkMagenta;
		case 'Y':    return Color::brown;
		case 'W':    return Color::white;
		case 'S':    return Color::gray;
		case '-':    return Color::darkGray;

		default: return Color::black;
	}
}
