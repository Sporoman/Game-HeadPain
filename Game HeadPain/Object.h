#ifndef OBJECT_H
#define OBJECT_H

#include "Coord.h"
#include "consoleColor//ConsoleColor.h"

enum class Entity;
enum class DirMove;

class Object
{
private:
	static int __countObjects;

	int _id;
	Entity _entity;
	Coord _coord;
	unsigned char _mapSymbol;		// Symbol on the physical map (before render)
	unsigned char _renderSymbol;	// Symbol on the visual map (after render)
	ccolor::Color _colorSymbol;		// Symbol color

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
	virtual ccolor::Color GetColor();
	

private:
	void MoveOnUp();
	void MoveOnLeft();
	void MoveOnRight();
	void MoveOnDown();

	//void GetInitializeMapSymbol(Entity entity);
	Entity GetInitializeEntity(unsigned char mapSymbol);
	unsigned char GetInitializeRenderSymbol(Entity entity);
	ccolor::Color GetInitializeColorSymbol(Entity entity);

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