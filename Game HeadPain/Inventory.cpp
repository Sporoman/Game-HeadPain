#include "Inventory.h"

Inventory::Inventory()
{
	_crystals = 0;
	_hearts   = 0;
	_keys     = 0;
	_levelKey = false;
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(Item item, int count)
{
	switch (item)
	{
		case Item::crystal:	   _crystals += count;   break;
		case Item::heart:	   _hearts   += count;	 break;
		case Item::key:		   _keys     += count;	 break;
		case Item::levelKey:   _levelKey  = true;	 break;
	}
}

void Inventory::TakeItem(Item item, int count)
{
	switch (item)
	{
		case Item::crystal:	   _crystals -= count;	 break;
		case Item::heart:	   _hearts   -= count;	 break;
		case Item::key:		   _keys     -= count;	 break;
		case Item::levelKey:   _levelKey  = false;	 break;
	}
}

void Inventory::SetItemCount(Item item, int count)
{
	switch (item)
	{
		case Item::crystal:    _crystals = count;	break;
		case Item::heart:	   _hearts   = count;   break;
		case Item::key:		   _keys     = count;	break;
		case Item::levelKey:   _levelKey = (count > 0 ? true : false);   break;
	}
}

int Inventory::GetItemCount(Item item) const
{
	switch (item)
	{
		case Item::crystal:    return _crystals;
		case Item::heart:	   return _hearts;
		case Item::key:		   return _keys;
		case Item::levelKey:   return _levelKey;
	}
}

void Inventory::SetInventory(const Inventory* inv)
{
	_crystals = inv->GetItemCount(Item::crystal);
	_hearts   = inv->GetItemCount(Item::heart);
	_keys     = inv->GetItemCount(Item::key);
	_levelKey = inv->GetItemCount(Item::levelKey);
}

bool Inventory::CheckKey()
{
	return _keys > 0 ? true : false;
}

bool Inventory::CheckLevelkey()
{
	return _levelKey;
}

void Inventory::Reset()
{
	_crystals = 0;
	_hearts   = 0;
	_keys     = 0;
	_levelKey = false;
}