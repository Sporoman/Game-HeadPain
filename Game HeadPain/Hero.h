#ifndef HERO_H
#define HERO_H

#include "Object.h"

class Hero : public Object
{
private:
	static unsigned char __mapSym;

	int _crystal_count;
	bool _lvl_key;

public:
	Hero(unsigned char renSym, ccolor::Color colSym, Coord coord);
	Hero(unsigned char renSym, ccolor::Color colSym);
	~Hero();

	void AddCrystal();
	void AddCrystal(int count);
	void SetCrystal(int count);
	void GiveLvlKey();
	void TakeLvlKey();
};

#endif // HERO_H