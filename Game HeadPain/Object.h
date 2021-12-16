#ifndef OBJECT_H
#define OBJECT_H

#include "Coord.h"
#include "consoleColor//Colors.h"

enum class Entity;
enum class DirMove;

class Object
{
private:
	static int __idObjects;			// To issue id to objects
	static int __countObjects;		// Total number of objects

	int    _id;
	Entity _entity;
	Coord  _coord;
	unsigned char _mapSymbol;		// Symbol on the physical map (before render)
	unsigned char _renderSymbol;	// Symbol on the visual map (after render)
	ccolors::Color _colorSymbol;		// Symbol color

public:
	Object(unsigned char mapSymbol, Coord coord);
	Object(unsigned char mapSymbol);
	~Object();

	static int GetObjectsCount();

	virtual void MoveOn(DirMove dir);
	virtual void SetCoord(int x, int y);
	virtual void SetCoord(Coord coord);

	virtual Entity GetEntity();
	virtual Coord GetCoord();
	virtual unsigned char GetMapSymbol();
	virtual unsigned char GetRenderSymbol();
	virtual ccolors::Color GetColor();
	

private:
	void MoveOnUp();
	void MoveOnLeft();
	void MoveOnRight();
	void MoveOnDown();

	//void GetInitializeMapSymbol(Entity entity);
	Entity GetInitializeEntity(unsigned char mapSymbol);
	unsigned char GetInitializeRenderSymbol(Entity entity);
	ccolors::Color GetInitializeColorSymbol(Entity entity);

};

enum class Entity
{
	error,
	empty,
	hero,
	wall,
	door,
	levelDoor,
	key,
	levelKey,
	box,
	exitDoor,
	crystal,
	mine,
	fogOfWar
};

enum class DirMove
{
	up    = 0,
	left  = 1,
	down  = 2,
	right = 3,
};

#endif // OBJECT_H