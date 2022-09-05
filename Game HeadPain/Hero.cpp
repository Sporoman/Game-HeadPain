#include "Hero.h"

unsigned char Hero::__mapSym = 'H';

Hero::Hero(Coord coord)
	: Object(__mapSym, coord), _inv{ 0, 0, false }
{
}

Hero::Hero()
	: Hero(Coord{0,0})
{
}

Hero::~Hero()
{}

void Hero::AddItem(Item item)
{
	AddItem(item, 1);
}

void Hero::AddItem(Item item, int count)
{
	switch (item)
	{
		case Item::crystal:	_inv.crystals += count;		break;
		case Item::heart:	_inv.hearts += count;		break;
		case Item::key:		_inv.keys += count;			break;
		case Item::lvlKey:	_inv.lvlKey = true;			break;

		default: break;
	}
}

void Hero::TakeItem(Item item)
{
	TakeItem(item, 1);
}

void Hero::TakeItem(Item item, int count)
{
	switch (item)
	{
		case Item::crystal:	_inv.crystals -= count;		break;
		case Item::heart:	_inv.hearts -= count;		break;
		case Item::key:		_inv.keys -= count;			break;
		case Item::lvlKey:	_inv.lvlKey = false;		break;

		default: break;
	}
}

void Hero::SetItem(Item item, int count)
{
	switch (item)
	{
		case Item::crystal:	_inv.crystals = count;	break;
		case Item::heart:	_inv.hearts = count;	break;
		case Item::key:		_inv.keys = count;		break;
		case Item::lvlKey:	_inv.lvlKey = (count > 0 ? true : false);	break;

		default: break;
	}
}

Inventory Hero::GetInventory()
{
	return _inv;
}

void Hero::SetInventory(const Inventory& inv)
{
	_inv = inv;
}

bool Hero::CheckKey()
{
	return _inv.keys > 0 ? true : false;
}

bool Hero::CheckLvlkey()
{
	return _inv.lvlKey;
}