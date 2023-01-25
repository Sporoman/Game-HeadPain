#ifndef INVENTORY_H
#define INVENTORY_H

enum class Item;

class Inventory
{
	int _crystals;
	int _hearts;
	int _keys;
	bool _levelKey;

public:
	Inventory();
	~Inventory();

	void SetInventory(const Inventory* inv);
	
	void AddItem(Item item,  int count = 1);
	void TakeItem(Item item, int count = 1);
	void SetItemCount(Item item,  int count);
	int  GetItemCount(Item item) const;

	bool CheckKey();
	bool CheckLevelkey();

	void Reset();
};

enum class Item
{
	crystal,
	heart,
	key,
	levelKey
};

#endif // INVENTORY_H