#include "Game.h"
#include "KeyDown.h"

Game::Game() 
	: _isGameActive(false), _hardMode(false), _successfulBkgRead(false), _activeLevel(0)
{
	// Initialize support systems
	_manager   = new GameManager();
	_settings  = _manager->GetSettings();
	
	const int renSizeX = _settings->lvlSizeX + _settings->hudMaxSizeX;
	const int renSizeY = _settings->lvlSizeY + _settings->hudMaxSizeY;
	_renSys = new RenderSystem(renSizeY, renSizeX);

	// Initialize hero object
	_hero = new Hero();

	// Initialize inventories
	_levelInv      = new Inventory();
	_heroBackupInv = new Inventory();

	// Initialize clone objects
	_cloneObjects = new Object* [I_SIZE];
	_cloneObjects[I_EMPTY] = new Object(Entity::empty);
	_cloneObjects[I_WALL]  = new Object(Entity::wall);
	_cloneObjects[I_FOG]   = new Object(Entity::fog);

	// Initialize maps of objects and fog
	_objectsMap = new Object** [_settings->lvlSizeY];
	_fogMap = new bool* [_settings->lvlSizeY];

	for (int y = 0; y < _settings->lvlSizeY; ++y)
	{
		_objectsMap[y] = new Object* [_settings->lvlSizeX];
		_fogMap[y] = new bool[_settings->lvlSizeX] { false };

		for (int x = 0; x < _settings->lvlSizeX; ++x)
			_objectsMap[y][x] = nullptr;
	}
}

Game::~Game()
{
	// Delete maps of objects and fog
	ClearObjectMap();
	for (int y = 0; y < _settings->lvlSizeY; ++y)
	{
		delete _objectsMap[y];
		delete _fogMap[y];
	}
	delete[] _objectsMap;
	delete[] _fogMap;

	// Delete user
	delete _hero;
	
	// Delete inventories
	delete _levelInv;
	delete _heroBackupInv;
	
	// Delete clone objects
	for (int i = 0; i < I_SIZE; ++i)
		delete _cloneObjects[i];

	// Delete support systems
	delete _renSys;
	delete _manager;
}

void Game::Start()
{
	ChooseMode();
	SetupSettings();
	_isGameActive = true;

	while (_activeLevel < _manager->GetSettings()->levelsCount)
	{
		Initialize();

		while (_isGameActive)
		{
			Render();
			Move();
		}

		_activeLevel++;
		_isGameActive = true;
	}

	Shutdown();
}

void Game::ChooseMode()
{
	_renSys->SendText(1, 4, "Choose mode (1 - s1mple, 2 - hard)");
	_renSys->Render();

	bool check = true;
	while(check)
	{
		switch (KeyDown::getWaitKey())
		{
			case Key::NUM_1:   check = false;	break;
			case Key::NUM_2:   check = false;	_hardMode = true;	break;

			default:
			_renSys->SendText(2, 4, "Just choose mode -_-", static_cast<Color>(rand() % 15 + 1));	// 15 Colors (without black)
			_renSys->Render();
		}
	}
}

void Game::SetupSettings()
{
	// Setting up the inventory
	_hero->GetInventory()->SetItemCount(Item::heart, _hardMode ? _settings->normalStartHearts : _settings->eazyStartHearts);
}

void Game::ClearObjectMap()
{
	for (int y = 0; y < _settings->lvlSizeY; ++y)
		for (int x = 0; x < _settings->lvlSizeX; ++x)
			DeleteObject(y, x);
}

void Game::Shutdown()
{
	_renSys->Clear();
	_renSys->SendText(1, 4, "Thank you for playing :) Bye - bye!");
	_renSys->Render();

	Sleep(3000);
	_renSys->Clear();
	_renSys->Render();
}

void Game::Initialize()
{
	// Set default items value on this level
	ResetLevelInventory();
	_successfulBkgRead = false;

	ClearObjectMap();

	// Load level and objects
	if (!_manager->ReadLevel(_activeLevel))
	{
		_isGameActive = false;
		return;
	}

	const std::string* level(_manager->GetLastLevel());
	for (int y = 0; y < _settings->lvlSizeY; ++y)
		for (int x = 0; x < _settings->lvlSizeX; ++x)
		{
			if (_hardMode)
				_fogMap[y][x] = true;

			unsigned char symbol = level->at(y * _settings->lvlSizeX + x);
			_objectsMap[y][x] = GetGameObject(Object::GetInitEntity(symbol));
			PlusItemCount(_objectsMap[y][x]->GetEntity(), _levelInv);

			if(_objectsMap[y][x]->GetEntity() == Entity::hero)
			{
				_objectsMap[y][x] = GetGameObject(Entity::empty);
				_hero->SetCoord(x, y);
			}
		}

	_renSys->Clear();

	// Render Background
	// if a background does not exists, just do not render it
	// if hard mode is false, draw the entire background
	// if hard mode is true, memorizing a successful background read for rendering during fog dispel
	if (_manager->ReadLevel(_activeLevel, true))
		if (!_hardMode)
		{
			const std::string* lvlBkg(_manager->GetLastLevel());
			for (int y = 0; y < _settings->lvlSizeY; ++y)
				for (int x = 0; x < _settings->lvlSizeX; ++x)
					if ((y * _settings->lvlSizeX + x) < lvlBkg->size())
						_renSys->DrawBkgCharColor(y, x, Object::GetInitColorFromBkgMap(lvlBkg->at(y * _settings->lvlSizeX + x)));
		}
		else
			_successfulBkgRead = true;
	
	// Remember the inventory state at the level start
	_heroBackupInv->SetInventory(_hero->GetInventory());

	// Dispelling the fog around the player
	Coord coord = _hero->GetCoord();
	DispelFog(coord.y, coord.x);
}

void Game::Render()
{
	RenderMap();
	RenderHud();
	RenderHero();
	_renSys->Render();
}

void Game::RenderMap()
{
	for (int y = 0; y < _settings->lvlSizeY; ++y)
		for (int x = 0; x < _settings->lvlSizeX; ++x)
			if (!_fogMap[y][x])
				_renSys->DrawChar(y, x, _objectsMap[y][x]->GetRenderObject());
			else
				_renSys->DrawChar(y, x, _cloneObjects[I_FOG]->GetRenderObject());
}

void Game::RenderHud()
{
	Inventory* inv = _hero->GetInventory();
	static const int x = _settings->lvlSizeX + _settings->hudIndentX; // X indent
	static const int y = _settings->lvlSizeY + 1;                     // Y indent

	SendHudText(2, x, "Level %i  ", _activeLevel + 1);
	SendHudText(4, x, "Level Key", Color::blue);
	inv->CheckItem(Item::levelKey) ? SendHudText(4, x+9, ": yeap", Color::blue) : SendHudText(4, x+9, ": nope");
	
	SendHudText(5, x,   "Keys", Color::yellow);
	SendHudText(5, x + 4, ": %i  ", inv->GetItemCount(Item::key));
	SendHudText(6, x,   "Hearts", Color::red);
	SendHudText(6, x+6, ": %i  ", inv->GetItemCount(Item::heart));
	SendHudText(7, x,   "Crystals", Color::darkMagenta);
	SendHudText(7, x+8, ": %i  ", inv->GetItemCount(Item::crystal));

	SendHudText(9, x,    "Keys", Color::yellow);
	SendHudText(9, x+4,  " on level: %i  ", _levelInv->GetItemCount(Item::key));
	SendHudText(10, x,   "Hearts", Color::red);
	SendHudText(10, x+6, " on level: %i  ", _levelInv->GetItemCount(Item::heart));
	SendHudText(11, x,   "Crystals", Color::darkMagenta);
	SendHudText(11, x+8, " on level: %i  ", _levelInv->GetItemCount(Item::crystal));

	SendHudText(13, x, "Hero X coord: %i  ", _hero->GetCoord().x);
	SendHudText(14, x, "Hero Y coord: %i  ", _hero->GetCoord().y);
	
	SendHudText(16, x, "Objects count: %i  ", Object::GetObjectsCount());
	
	SendHudText(y,   4,    "Use WASD to move ");
	SendHudText(y,   4+17, "Hero", Color::green);
	SendHudText(y+1, 4,    "Press ? to restart level.");
	SendHudText(y+1, 4+6,  "R", Color::red);
}

void Game::SendHudText(int y, int x, const char* text, Color symbolColor, Color bkgColor)
{
	static char textBuffer[50];

	sprintf_s(textBuffer, text, 50);
	_renSys->SendText(y, x, textBuffer, symbolColor, bkgColor);
}

void Game::RenderHero()
{
	Coord coord = _hero->GetCoord();
	_renSys->DrawChar(coord.y, coord.x, _hero->GetRenderObject());
}

void Game::SendHudText(int y, int x, const char* text, int count, Color symbolColor, Color bkgColor)
{
	static char textBuffer[50];

	sprintf_s(textBuffer, text, count, 50);
	_renSys->SendText(y, x, textBuffer, symbolColor, bkgColor);
}

void Game::Move()
{
	int x = _hero->GetCoord().x;
	int y = _hero->GetCoord().y;

	switch (KeyDown::getWaitKey())
	{
		case Key::W: case Key::KEY_UP:      MoveHeroTo(y-1, x);   break;
		case Key::S: case Key::KEY_DOWN:    MoveHeroTo(y+1, x);   break;
		case Key::A: case Key::KEY_LEFT:    MoveHeroTo(y, x-1);   break;
		case Key::D: case Key::KEY_RIGHT:   MoveHeroTo(y, x+1);   break;

		case Key::R:   RestartLevel();   break;

		case Key::NUM_1:   _activeLevel--;   Initialize();   break;
		case Key::NUM_2:   _activeLevel++;   Initialize();   break;	
	}
}

void Game::MoveHeroTo(int y, int x)
{
	if (x < 0 || y < 0 || x >= _settings->lvlSizeX || y >= _settings->lvlSizeY)
		return;

	Object* collidingObject = _objectsMap[y][x];

	bool canMove = true;
	switch (collidingObject->GetEntity())
	{
		case Entity::empty:   break;

		case Entity::crystal: case Entity::heart: case Entity::key: case Entity::levelKey:
		{
			MinusItemCount(collidingObject->GetEntity(), _levelInv);
			PlusItemCount(collidingObject->GetEntity(), _hero->GetInventory());

			break;
		}

		case Entity::mine:		 RestartLevel();                           return;
		case Entity::exitDoor:   _isGameActive = false;                    return;
		case Entity::box:        canMove = MoveHeroToBox(y, x);            break;
		case Entity::door:       canMove = TakeHeroItem(Item::key);        break;
		case Entity::levelDoor:  canMove = TakeHeroItem(Item::levelKey);   break;
		case Entity::fakeWall:   MoveHero(y, x);                           return;

		default:   canMove = false;
	}

	if (canMove)
		MoveHeroWithDelete(y, x);
}

void Game::MoveHero(int y, int x)
{
	_hero->SetCoord(x, y);

	if (_hardMode)
		DispelFog(y, x);
}

void Game::MoveHeroWithDelete(int y, int x)
{
	// Delete the colliding object, insert an empty and set the hero position
	DeleteObject(y, x);
	_objectsMap[y][x] = _cloneObjects[I_EMPTY];
	_hero->SetCoord(x, y);

	// Dispel fog
	if (_hardMode)
		DispelFog(y, x);
}

bool Game::MoveHeroToBox(int y, int x)
{
	// Hero move direction
	Coord heroCoord = _hero->GetCoord();
	int heroDirectionY = y - heroCoord.y;
	int heroDirectionX = x - heroCoord.x;

	int objBehindY = y + heroDirectionY;
	int objBehindX = x + heroDirectionX;

	// Check map border
	if (objBehindX < 0 || objBehindX >= _settings->lvlSizeX
		|| objBehindY < 0 || objBehindY >= _settings->lvlSizeY)
		return false;

	// Check space behind the box and handling collisions with objects
	Entity entityBehindBox = _objectsMap[objBehindY][objBehindX]->GetEntity();
	switch (entityBehindBox)
	{
		case Entity::crystal: case Entity::heart: case Entity::key: case Entity::levelKey:
		{
			// Bye bye, Jewel
			MinusItemCount(entityBehindBox, _levelInv);
			DeleteObject(objBehindY, objBehindX);
		}

		case Entity::empty:
		{
			// Replace box
			Object* boxObject = _objectsMap[y][x];
			_objectsMap[y][x] = _cloneObjects[I_EMPTY];
			_objectsMap[objBehindY][objBehindX] = boxObject;
		}
		return true;

		case Entity::mine:   RestartLevel();
		default:   return false;
	}
}

void Game::DispelFog(int y_pos, int x_pos)
{
	if (_hardMode && _successfulBkgRead)
	{
		const std::string* lvlBkg(_manager->GetLastLevel());
		for (int y = y_pos - 2; y <= y_pos + 2; ++y)
			for (int x = x_pos - 3; x <= x_pos + 3; ++x)
				if (x < _settings->lvlSizeX && y < _settings->lvlSizeY && x >= 0 && y >= 0
					&& (_fogMap[y][x] == true))
				{
					if ((y * _settings->lvlSizeX + x) < lvlBkg->size())
					{
						// Dispel the fog and redraw background symbol
						_fogMap[y][x] = false;
						_renSys->DrawBkgCharColor(y, x, Object::GetInitColorFromBkgMap(lvlBkg->at(y * _settings->lvlSizeX + x)));
					}
				}
	}
}

void Game::RestartLevel()
{
	// Set the inventory at the beginning of the level
	_hero->SetInventory(_heroBackupInv);

	// Take one heart
	_hero->GetInventory()->TakeItem(Item::heart);

	// Restart level
	Initialize();
}

void Game::DeleteObject(int y, int x)
{
	Object* obj = _objectsMap[y][x];

	if (_objectsMap[y][x] == nullptr)
		return;

	if (!isCloneObject(obj->GetEntity()))
		delete obj;

	_objectsMap[y][x] = nullptr;
}

Object* Game::GetGameObject(Entity entity)
{
	switch (entity)
	{
		case Entity::hero:     return _hero;

		case Entity::empty:    return _cloneObjects[I_EMPTY];
		case Entity::wall:     return _cloneObjects[I_WALL];
		case Entity::fog:      return _cloneObjects[I_FOG];

		case Entity::_error:   return nullptr;

		default:   return new Object(entity);
	}
}

void Game::ResetLevelInventory()
{
	_levelInv->Reset();
}

bool Game::TakeHeroItem(Item item)
{
	if (_hero->GetInventory()->CheckItem(item))
	{
		_hero->GetInventory()->TakeItem(item);
		return true;
	}
	
	return false;
}

void Game::SetItemCount(Entity entity, Inventory* inv, int count)
{
	switch (entity)
	{
		case Entity::crystal:   inv->SetItemCount(Item::crystal, count);    break;
		case Entity::heart:     inv->SetItemCount(Item::heart, count);      break;
		case Entity::key:       inv->SetItemCount(Item::key, count);        break;
		case Entity::levelKey:  inv->SetItemCount(Item::levelKey, count);   break;
	}
}

void Game::PlusItemCount(Entity entity, Inventory* inv)
{
	switch (entity)
	{
		case Entity::crystal:   inv->AddItem(Item::crystal);    break;
		case Entity::heart:     inv->AddItem(Item::heart);      break;
		case Entity::key:       inv->AddItem(Item::key);        break;
		case Entity::levelKey:  inv->AddItem(Item::levelKey);   break;
	}
}

void Game::MinusItemCount(Entity entity, Inventory* inv)
{
	switch (entity)
	{
		case Entity::crystal:   inv->TakeItem(Item::crystal);    break;
		case Entity::heart:     inv->TakeItem(Item::heart);      break;
		case Entity::key:       inv->TakeItem(Item::key);        break;
		case Entity::levelKey:  inv->TakeItem(Item::levelKey);   break;
	}
}

bool Game::isCloneObject(Entity entity)
{
	if (entity == Entity::empty || entity == Entity::wall || entity == Entity::fog)
		return true;

	return false;
}