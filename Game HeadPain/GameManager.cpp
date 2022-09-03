#include "GameManager.h"
#include <fstream>

// Сделать считывание файла настроек
// Предусмотреть, если он испорчен (использовать стандартные настройки)
// Пересоздать файл настроек
// ---------
// Сделать считывание карт из текстового файла

GameManager::GameManager()
{
	// Setup start settings
	_mapSettings["Levels"]   = _settings.levelsCount;
	_mapSettings["LvlSizeX"] = _settings.lvlSizeX;
	_mapSettings["LvlSizeY"] = _settings.lvlSizeY;
	_mapSettings["IndentForHudText"] = _settings.indentX;

	// Reading settings from a settings file
	ReadSettings();
}

GameManager::~GameManager()
{
}

const std::string* GameManager::GetLevel(int level, bool background)
{
	if (level < 0 || level >= _settings.levelsCount)
		return nullptr;

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
		return nullptr;

	// Reading level from a file
	std::string* levelStr = new std::string;
	std::string line;

	while (getline(file, line))
		levelStr->append(line);

	file.close();
	return levelStr;
}

const Settings* const GameManager::GetSettings()
{
	return &_settings;
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
	_settings.levelsCount = _mapSettings["Levels"];
	_settings.lvlSizeX = _mapSettings["LvlSizeX"];
	_settings.lvlSizeY = _mapSettings["LvlSizeY"];
	_settings.indentX  = _mapSettings["IndentForHudText"];
}