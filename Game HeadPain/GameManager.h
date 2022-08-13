#ifndef MAPMANAGER
#define MAPMANAGER

#include <string>
#include <map>

class GameManager
{
private:
	static const std::string s_levelsPath;
	static const std::string s_mapFileName;
	static const std::string s_extensionName;
	static const std::string s_settingsFileName;

	// Game Settings
	std::map <std::string, int> _settings;
	static const int _levelsCount = 7;
	static const int _lvlSizeY    = 21;
	static const int _lvlSizeX    = 40;
	static const int _indentX     = 5;

public:
	GameManager();
	~GameManager();

	const char* GetLevel(int level);

	const std::map <std::string, int>* const GetSettings();

private:
	bool ReadSettings();
};

#endif // !MAPMANAGER