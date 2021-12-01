#include "Hero.h"

unsigned char Hero::__mapSym = 'H';

Hero::Hero(unsigned char renSym, ccolor::Color colSym, Coord coord)
	: Object(__mapSym, renSym, colSym, coord),
	_crystal_count(0), _lvl_key(false)
{
}

Hero::Hero(unsigned char renSym, ccolor::Color colSym)
	: Hero(renSym, colSym, Coord{0,0})
{
}

Hero::~Hero()
{}

void Hero::AddCrystal()
{
	++_crystal_count;
}

void Hero::AddCrystal(int count)
{
	_crystal_count += count;
}

void Hero::SetCrystal(int count)
{
	_crystal_count = count;
}

void Hero::GiveLvlKey()
{
	_lvl_key = true;
}

void Hero::TakeLvlKey()
{
	_lvl_key = false;
}
