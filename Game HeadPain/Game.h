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

	Inventory _inventoryAtLevelStart;
	int _activeLevel;
	int _crystalsOnLvl;
	int _heartsOnLvl;
	int _keysOnLvl;

	static const int I_EMPTY = 0;
	static const int I_WALL  = 1;
	static const int I_FOG   = 2;
	static const int I_SIZE  = 3;

	Hero* _hero;
	Object** _cloneObjects;
	bool** _fogMap;
	Object*** _objectsMap;

public:
	Game();
	~Game();

	void Start();

private:
	void ChooseMode();
	void SetupSettings();
	void Shutdown();

	void Initialize();
	void Render();
	void Move();

	void RenderMap();
	void RenderHud();
	void RenderHero();
	void SendHudText(int y, int x, const char* text, Color symbolColor = Color::gray, Color bkgColor = Color::black);
	void SendHudText(int y, int x, const char* text, int count, Color symbolColor = Color::gray, Color bkgColor = Color::black);
	void MoveHeroTo(int y, int x);
	void DispelFog(int y, int x);
	void RestartLevel();

	Object* GetGameObject(Entity entity);
	void DeleteNormalObject(Coord coord);
	void ClearObjectMap();
	void SetDefaultItemsValueOnLvl();

	bool isCloneObject(Object* obj);
	bool isCloneObject(Entity entity);
};

#endif // GAME_H