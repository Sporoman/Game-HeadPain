#ifndef HERO_H
#define HERO_H

#include "Object.h"
#include "Inventory.h"

struct Coord
{
	int x = 0;
	int y = 0;
};


class Hero : public Object
{
	Inventory* _inv;
	Coord _coord;

public:
	Hero(Coord coord);
	Hero();
	~Hero();

	Inventory* GetInventory();
	void SetInventory(const Inventory* inv);

	Coord GetCoord();
	void SetCoord(int x, int y);
	void SetCoord(Coord coord);
};

#endif // HERO_H