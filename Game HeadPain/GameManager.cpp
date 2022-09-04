#include "GameManager.h"
#include <fstream>


GameManager::GameManager()
{
	_settings  = new Settings();
	_lastLevel = new std::string();

	// Setup start settings
	_mapSettings["Levels"]      = _settings->levelsCount;
	_mapSettings["LvlSizeX"]    = _settings->lvlSizeX;
	_mapSettings["LvlSizeY"]    = _settings->lvlSizeY;
	_mapSettings["HudIndentX"]  = _settings->hudIndentX;
	_mapSettings["HudMaxSizeX"] = _settings->hudMaxSizeX;
	_mapSettings["HudMaxSizeY"] = _settings->hudMaxSizeY;

	// Reading settings from a settings file
	ReadSettings();
}

GameManager::~GameManager()
{
	delete _settings;
	delete _lastLevel; 
}

bool GameManager::ReadLevel(int level, bool background)
{
	if (level < 0 || level >= _settings->levelsCount)
		return false;

	// Opening selected level
	std::string fileName;

	// Check background
	if (background)
		fileName = "levels/b_level_";
	else
		fileName = "levels/level_";

	fileName.append(std::to_string(level));
	fileName.append(".txt");

	std::fstream file(fileName, std::ios_base::in);
	if (!file.is_open())
		return false;

	// Reading level from a file
	std::string line;

	_lastLevel->clear();
	while (getline(file, line))
		_lastLevel->append(line);

	file.close();
	return true;
}

const std::string* GameManager::GetLastLevel()
{
	return _lastLevel;
}

const Settings* const GameManager::GetSettings()
{
	return _settings;
}

bool GameManager::ReadSettings()
{
	std::fstream file("settings.txt", std::ios_base::in);
	if (!file.is_open())
		return false;

	std::string str;
	while (getline(file, str))
	{
		auto pos = str.find('=');
		if (pos != std::string::npos)
		{
			std::string param = str.substr(0, pos);
			std::string value = str.substr(pos + 1);

			auto it = _mapSettings.find(param);
			if (it != _mapSettings.end())
				it->second = stoi(value);
		}
	}

	file.close();

	// Loading the read settings
	SetupSettings();

	return true;
}

void GameManager::SetupSettings()
{
	_settings->levelsCount = _mapSettings["Levels"];
	_settings->lvlSizeX    = _mapSettings["LvlSizeX"];
	_settings->lvlSizeY    = _mapSettings["LvlSizeY"];
	_settings->hudIndentX  = _mapSettings["HudIndentX"];
	_settings->hudMaxSizeX = _mapSettings["HudMaxSizeX"];
	_settings->hudMaxSizeY = _mapSettings["HudMaxSizeY"];
}