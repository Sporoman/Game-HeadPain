#ifndef OBJECT_H
#define OBJECT_H

#include "Coord.h"
#include "renderSystem//colors.h"
#include "renderSystem//RenderObject.h"

enum class Entity;
enum class DirMove;

class Object
{
private:
	static int __idObjects;		// To give id to objects
	static int __countObjects;	// Total number of objects

	int    _id;
	Entity _entity;
	Coord  _coord;
	unsigned char _mapSymbol;	// Symbol on the physical map (before render)
	RenderObject  _renderObj;	// struct: symbol + color symbol + color backgorund

public:
	Object(unsigned char mapSymbol);
	Object(unsigned char mapSymbol, Coord coord);
	Object(Entity entity);
	Object(Entity entity, Coord coord);
	~Object();

	static int GetObjectsCount();

	virtual void MoveOn(DirMove dir);
	virtual void SetCoord(int x, int y);
	virtual void SetCoord(Coord coord);

	virtual Entity GetEntity();
	virtual Coord GetCoord();
	virtual unsigned char GetMapSymbol();
	virtual unsigned char GetRenderSymbol();
	virtual Color GetColorSymbol();
	virtual Color GetColorBackground();
	virtual const RenderObject& GetRenderObject();
	
	static Color GetInitializeColorBackgroundFromMap(unsigned char symbol);    // Test
	static Entity GetInitializeEntity(unsigned char mapSymbol);
	static unsigned char GetInitializeMapSymbol(Entity entity);
	static unsigned char GetInitializeRenderSymbol(Entity entity);
	static Color GetInitializeColorSymbol(Entity entity);
	static Color GetInitializeColorBackground(Entity entity);

private:
	void MoveOnUp();
	void MoveOnLeft();
	void MoveOnRight();
	void MoveOnDown();
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