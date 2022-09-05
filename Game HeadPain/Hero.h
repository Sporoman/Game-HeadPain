#ifndef HERO_H
#define HERO_H

#include "Object.h"
#include "Inventory.h"

enum class Item;

class Hero : public Object
{
private:
	static unsigned char __mapSym;

	Inventory _inv;

public:
	Hero(Coord coord);
	Hero();
	~Hero();

	Inventory GetInventory();
	void SetInventory(const Inventory& inv);

	void AddItem(Item item);
	void AddItem(Item item, int count);
	void TakeItem(Item item);
	void TakeItem(Item item, int count);
	void SetItem(Item item, int count);
	

	bool CheckKey();
	bool CheckLvlkey();
};

enum class Item
{
	crystal,
	key,
	lvlKey
};

#endif // HERO_H