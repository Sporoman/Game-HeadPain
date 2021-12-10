#ifndef HERO_H
#define HERO_H

#include "Object.h"
#include "Inventory.h"

//enum class Item
//{
//	crystal = 0,
//	key = 1,
//};

class Hero : public Object
{
private:
	static unsigned char __mapSym;

	Inventory _inventory;

public:
	Hero(unsigned char renSym, ccolor::Color colSym, Coord coord);
	Hero(unsigned char renSym, ccolor::Color colSym);
	~Hero();

	void AddCrystal();
	void AddCrystal(int count);
	void SetCrystal(int count);

	void AddKey();
	void AddKey(int count);
	void SetKey(int count);

	Inventory GetInventory();

	//void AddItem(Item item);
	//void AddItem(Item item, int count);
	//void SetItem(Item item, int count);

	bool CheckLvlkey();
	void GiveLvlKey();
	void TakeLvlKey();
};

#endif // HERO_H