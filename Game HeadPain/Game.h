#ifndef GAME_H
#define GAME_H

#include "renderSystem/renderSystem.h"
#include "GameManager.h"
#include "Object.h"
#include "Hero.h"

class Game
{
	bool _isGameActive;
	bool _hardMode;
	bool _successfulBkgRead;

	RenderSystem* _renSys;
	GameManager* _manager;
	const Settings* _settings;

	Inventory* _levelInv;
	Inventory* _heroBackupInv;

	static const int I_EMPTY = 0;
	static const int I_WALL  = 1;
	static const int I_FOG   = 2;
	static const int I_SIZE  = 3;
	Object** _cloneObjects;

	int _activeLevel;
	Hero* _hero;
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
	void DeleteObject(int y, int x);
	void ClearObjectMap();
	void ResetLevelInventory();
	void SetItemCount(Entity entity, Inventory* inv, int count);
	void PlusItemCount(Entity entity, Inventory* inv);
	void MinusItemCount(Entity entity, Inventory* inv);
	bool isCloneObject(Entity entity);
};

#endif // GAME_H