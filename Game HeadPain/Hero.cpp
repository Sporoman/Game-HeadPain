#include "Hero.h"

Hero::Hero(Coord coord) : Object(Entity::hero),
	_coord(coord)
{
	_inv = new Inventory();
}

Hero::Hero() : Hero(Coord{0,0})
{
}

Hero::~Hero()
{
	delete _inv;
}

Inventory* Hero::GetInventory()
{
	return _inv;
}

void Hero::SetInventory(const Inventory* inv)
{
	_inv->SetInventory(inv);
}

Coord Hero::GetCoord()
{
	return _coord;
}

void Hero::SetCoord(int x, int y)
{
	SetCoord(Coord{x, y});
}

void Hero::SetCoord(Coord coord)
{
	_coord.x = coord.x;
	_coord.y = coord.y;
}
