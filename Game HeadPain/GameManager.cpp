#include "GameManager.h"
#include <fstream>

// Сделать считывание файла настроек
// Предусмотреть, если он испорчен (использовать стандартные настройки)
// Пересоздать файл настроек
// ---------
// Сделать считывание карт из текстового файла

const std::string GameManager::s_levelsPath    = "levels/";
const std::string GameManager::s_mapFileName   = "map";
const std::string GameManager::s_extensionName = ".txt";
const std::string GameManager::s_settingsFileName  = "settings.txt";

GameManager::GameManager()
{
	// Filling the settings map with settings
	_settings["Levels"]   = _levelsCount;
	_settings["LvlSizeX"] = _lvlSizeX;
	_settings["LvlSizeY"] = _lvlSizeY;
	_settings["IndentForHudText"] = _indentX;

	// Read settings from settings file
	ReadSettings();
}

GameManager::~GameManager()
{
}

const char* GameManager::GetLevel(int level)
{
	std::string fileName("map1.txt");
	std::fstream file(s_settingsFileName, std::ios_base::in);

	std::string str;
	while (getline(file, str))
	{
		auto pos = str.find('=');
		if (pos != std::string::npos)
		{
			std::string param = str.substr(0, pos);
			std::string value = str.substr(pos + 1);

			auto it = _settings.find(param);
			if (it != _settings.end())
				it->second = stoi(value);
		}
	}

	file.close();
}

const std::map<std::string, int>* const GameManager::GetSettings()
{
	return &_settings;
}

bool GameManager::ReadSettings()
{
	std::fstream file("settings.txt", std::ios_base::in);
	
	std::string str;
	while (getline(file, str))
	{
		auto pos = str.find('=');
		if (pos != std::string::npos)
		{
			std::string param = str.substr(0, pos);
			std::string value = str.substr(pos + 1);

			auto it = _settings.find(param);
			if (it != _settings.end())
				it->second = stoi(value);
		}
	}

	file.close();

	return false;
}
