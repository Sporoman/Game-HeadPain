#ifndef MAPMANAGER
#define MAPMANAGER

#include <string>
#include <map>

struct Settings;

class GameManager
{
private:
	std::map <std::string, int> _mapSettings;
	Settings* _settings;
	std::string* _lastLevel;

public:
	GameManager();
	~GameManager();

	bool ReadLevel(int level, bool bkgFile = false);
	const std::string* GetLastLevel();
	const Settings* const GetSettings();

private:
	bool ReadSettings();
	void SetupSettings();
};

struct Settings 
{
	int levelsCount = 7;
	int lvlSizeY = 21;
	int lvlSizeX = 40;
	int hudIndentX = 5;
	int hudMaxSizeX = 25;
	int hudMaxSizeY = 10;
	int eazyStartHearts = 10;
	int normalStartHearts = 3;
};

#endif // !MAPMANAGER