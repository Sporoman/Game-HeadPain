#ifndef GAME_H
#define GAME_H

#include "renderSystem/renderSystem.h"
#include "GameManager.h"
#include "Object.h"
#include "Hero.h"
	
class Game
{
private:
	bool _isGameActive;
	bool _hardMode;
	bool _successfulBkgRead;

	RenderSystem* _renSys;
	GameManager* _manager;
	const Settings* _settings;

	Hero*   _hero;
	Object* _empty;
	Object* _wall;
	Object* _fogOfWar;

	Inventory _inventoryAtLevelStart;
	int _activeLevel;
	int _crystalsOnLvl;
	int _keysOnLvl;

	bool** _fogOfWarB;
	Object*** _objectsMap;

public:
	Game();
	~Game();

	void Start();

private:
	void ChooseMode();
	void ClearObjectMap();
	Object* CreateObject(unsigned char symbol, Coord coord);
	void Shutdown();

	void Initialize();
	void Render();
	void RenderHud();
	void RestartLevel();
	void Move();
	void MoveHeroTo(int y, int x);
	void DispelFogOfWar(int y, int x);
	void SetDefaultItemsValueOnLvl();
};

#endif // GAME_H