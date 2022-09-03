#ifndef MAPMANAGER
#define MAPMANAGER

#include <string>
#include <map>

struct Settings;

class GameManager
{
private:
	std::map <std::string, int> _mapSettings;
	Settings _settings;

public:
	GameManager();
	~GameManager();

	const std::string* GetLevel(int level, bool background = false);

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
	int indentX = 5;
};

#endif // !MAPMANAGER