#include "Hero.h"

unsigned char Hero::__mapSym = 'H';

Hero::Hero(unsigned char renSym, ccolor::Color colSym, Coord coord)
	: Object(__mapSym, renSym, colSym, coord),
	_inventory{ 0, 0, false }
{
}

Hero::Hero(unsigned char renSym, ccolor::Color colSym)
	: Hero(renSym, colSym, Coord{0,0})
{
}

Hero::~Hero()
{}

//void Hero::AddItem(Item item)
//{
//	switch (item)
//	{
//		case Item::crystal:		
//		case Item::key:
//
//		default: break;
//	}
//}
//
//void Hero::AddItem(Item item, int count)
//{
//
//}
//
//void Hero::SetItem(Item item, int count)
//{
//
//}

void Hero::AddCrystal()
{
	++_inventory.crystal_count;
}

void Hero::AddCrystal(int count)
{
	_inventory.crystal_count += count;
}

void Hero::SetCrystal(int count)
{
	_inventory.crystal_count = count;
}

void Hero::AddKey()
{
	++_inventory.key_count;
}

void Hero::AddKey(int count)
{
	_inventory.key_count += count;
}

void Hero::SetKey(int count)
{
	_inventory.key_count = count;
}

bool Hero::CheckLvlkey()
{
	return _inventory.lvl_key == true ? true : false;
}

void Hero::GiveLvlKey()
{
	_inventory.lvl_key = true;
}

void Hero::TakeLvlKey()
{
	_inventory.lvl_key = false;
}
