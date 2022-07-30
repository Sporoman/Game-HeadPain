#ifndef GAME_H
#define GAME_H

#include <conio.h>
#include "renderSystem/renderSystem.h"
#include "Object.h"
#include "Hero.h"

class Game
{
private:
	bool _isGameActive;
	bool _hardMode;

	RenderSystem* _renSys;

	Hero*   _hero;
	Object* _empty;
	Object* _wall;

	Inventory _inventoryAtLevelStart;
	int _activeLevel;
	int _crystalsOnLvl;
	int _keysOnLvl;

	const int _lvlSizeY = 21;
	const int _lvlSizeX = 40;
	const int _levelsCount = 7;

	Object* _objectsMap[21][40];
	
public:
	Game();
	~Game();

	void Start();
	void Initialize();
	void Render();
	void RestartLevel();

	void Move();
	void MoveHeroTo(int y, int x);

	void Shutdown();

private:
	void ChooseMode();
	Object* CreateObject(unsigned char symbol, Coord coord);

	void SetDefaultItemsValueOnLvl();
	void DispelFogOfWar(int y, int x);

	static const unsigned char mapSymbol_fogOfWar = 176;
	static const unsigned char mapSymbol_empty = ' ';
	static const unsigned char mapSymbol_hero = 'H';
	static const unsigned char mapSymbol_wall = '#';
	static const unsigned char mapSymbol_door = 'D';
	static const unsigned char mapSymbol_levelDoor = '[';
	static const unsigned char mapSymbol_key = 'K';
	static const unsigned char mapSymbol_levelKey = ']';
	static const unsigned char mapSymbol_box = 'B';
	static const unsigned char mapSymbol_exit = 'E';
	static const unsigned char mapSymbol_crystal = 'C';
	static const unsigned char mapSymbol_mine = 'M';

	const int lvlSizeY = 21;
	const int lvlSizeX = 40;
	const int levelsCount = 7;

	bool fogOfWarB[21][40]{ false };

	// Все объекты используют светлые цвета, а фон - тёмные (кроме ящика - он коричневый (тёмно-жёлтый))
	const unsigned char levelsData[7][21][40 + 1] = {
																	{
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"###B       #  B    #B#    B  #      B###",
																		"##B        B                 B       B##",
																		"## H B B   B     B#B#B#B     BC K#   D E",
																		"##B        B                 B       B##",
																		"###B       #  B    #B#    B  #      B###",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																	} ,
																	{
																		"########################################",
																		"######################D#################",
																		"#######################D################",
																		"##############DDDDDDDDDDD###############",
																		"#######################D################",
																		"######################D#################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"######   M C M   #M C    BM       ###D##",
																		"#### H   #####C  B  M#   C  ]#C   C [ED#",
																		"######      BC  ##   C   BM       ###D##",
																		"########################################",
																		"########################################",
																		"########################################",
																		"######################D#################",
																		"#######################D################",
																		"##############DDDDDDDDDDD###############",
																		"#######################D################",
																		"######################D#################",
																		"########################################",
																	} ,
																	{
																		"########################################",
																		"##      M####     B    ##K B   D   CBK##",
																		"#D  H    K  D   ####  ####  M  #B   MC##",
																		"##      M####   C#C   C    B   #  B   ##",
																		"##########CCD   ################D#######",
																		"##CM CB   ###   #C     C#  K#K #   BC###",
																		"## B  C#        ##BMB MB  BM##  #  M  ##",
																		"##    B#  ###   D CM     #C D M     B ##",
																		"##K###    ### B # #    ##   # #B    C###",
																		"###   ####### K # #  B  # B #C    # BK##",
																		"##  #B     K#D#D#   MCM     #M#M  C  C##",
																		"## #   ###### # ########################",
																		"#    BB#    B # B     #   #     M##MMM##",
																		"###BB  ##CC########CC#M M  M #M  M MKM##",
																		"##  B BBB  B###   #B M   M   M M   M ###",
																		"##  B#B   BBB D   D    M   M   M M  C###",
																		"# B   BB B B  #   ######################",
																		"###B    B BB  #                    #D###",
																		"##B B BB   #BB#         ]          [ED##",
																		"##C  #B  B    #                    #D###",
																		"########################################",
																	} ,
																	{
																		"########################################",
																		"## #B   B ############ B   #    B # B ##",
																		"##  B  B # B  B    #BB#B  B     # #B   E",
																		"## B#B  #BBB  B # B    # #B# #B  B# BB##",
																		"## B## B#B ### B##### B#B  B# #B  # B ##",
																		"##B  #  #     B  #B   B#      # BB##  ##",
																		"##   #  #######  ## #####BB#BB#B B#BB ##",
																		"## #B #B B B B## # B B #B# B  #    # ###",
																		"##B BB# # B B ## #B B    #   B## B #  ##",
																		"##### #B#B B B# B# B BB# # B    #  #  ##",
																		"##  #  #### ##B  B###### BB  #B# B B# ##",
																		"## H #  #B  BB  #     B#B #  B #  B # ##",
																		"##B  #  # B B #  B #B  #  ##BB  #  B# ##",
																		"##B B# B#  B##B  B## BB#  # B  B #  B ##",
																		"## B #  ## B ###### B ##BB#B# B B #B  ##",
																		"##B B # B## B   B B  ##  BB  #BB BB#  ##",
																		"##   B B  ## BB  B  ##   #  BB     # ###",
																		"##B #B BB# ###  B  ##  B# #B B ### #  ##",
																		"## B     # B ######B  B#     BB  B  # ##",
																		"## B B#B #B B BB  B  B    #B  B  B B ###",
																		"########################################",
																	} ,
																	{

																		"########################################",
																		"##KMB     M   B    C#  M    B  B      ##",
																		"##C   M  B  B#CM  B #    C  M    MC BB##",
																		"## M  C  M B #B  M  CM  B#M B #CB BM  ##",
																		"##C B MC   C #  B   #  M CB  #K#      ##",
																		"##B   ######### M   #  B    #  #   C  ##",
																		"## BMC#  BMC  #   MC#M   M #M  #  M#  ##",
																		"##  BM#     MB##D#######D##MC B#  B  B##",
																		"##C   DC####  #M B M#E  C #CMB #      ##",
																		"########C CB  #  B #C B B #   M##B MMC##",
																		"##CCCCCC# M B #KCB H#   BC#   B C#    ##",
																		"##  M   #   C ############# M  BC##   ##",
																		"## B M  #MB M#     CM   C   B   #  BMB##",
																		"##B B  #    #  BM  MB    MB  M  #     ##",
																		"##   M#CM MB#CB B B   M     B   #CM   ##",
																		"## C   #     #  MB ########MC B#MB  C ##",
																		"##BBM  K# BM B#   # C      ####KB   BB##",
																		"## B   #C#   M #D# C B# BB     #M  M  ##",
																		"## B      BMB B   B      B M  BC#    B##",
																		"##C B M        MC  B   M     B     B B##",
																		"########################################",
																	} ,
																	{
																		"#####E##################################",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##             H                      ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"##                                    ##",
																		"########################################",
																	} ,
	};

	// # and 0 = Чёрный
	// B = Тёмно-синий
	// G = Тёмно-зелёный
	// C = Голубой
	// R = Красный
	// M = Пурпурный
	// Y = Тёмно-жёлтый (+-коричневый)
	// W = белый
	// S = Тёмно-серый
	// - = Серый

	const unsigned char levelsBackgroundData[7][21][40 + 1] = {
																	{
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"###   -----#--   --# #- -----#BBBBBBS###",
																		"##   --- ----------  ---- ---BBBBBBBSS##",
																		"## H-- --------- -#-# #-----BBBBB#BBBSSM",
																		"##   ---- ---- --------   -- BBBBBBBSS##",
																		"###  -  ---#- --- -#-#-------#BBBBBBS###",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"########################################",
																	} ,
																	{
																		"########################################",
																		"######################D#################",
																		"#######################D################",
																		"##############DDDDDDDDDDD###############",
																		"#######################D################",
																		"######################D#################",
																		"########################################",
																		"########################################",
																		"########################################",
																		"######   M C M   #M C    BM       ###D##",
																		"#### H   #####C  B  M#   C  ]#C   C [ED#",
																		"######      BC  ##   C   BM       ###D##",
																		"########################################",
																		"########################################",
																		"########################################",
																		"######################D#################",
																		"#######################D################",
																		"##############DDDDDDDDDDD###############",
																		"#######################D################",
																		"######################D#################",
																		"########################################",
																	} ,
																	{
																		"########################################",
																		"##      M####     B    ##K B   D   CBK##",
																		"#D  H    K  D   ####  ####  M  #B   MC##",
																		"##      M####   C#C   C    B   #  B   ##",
																		"##########CCD   ################D#######",
																		"##CM CB   ###   #C     C#  K#K #   BC###",
																		"## B  C#        ##BMB MB  BM##  #  M  ##",
																		"##    B#  ###   D CM     #C D M     B ##",
																		"##K###    ### B # #    ##   # #B    C###",
																		"###   ####### K # #  B  # B #C    # BK##",
																		"##  #B     K#D#D#   MCM     #M#M  C  C##",
																		"## #   ###### # ########################",
																		"#    BB#    B # B     #   #     M##MMM##",
																		"###BB  ##CC########CC#M M  M #M  M MKM##",
																		"##  B BBB  B###   #B M   M   M M   M ###",
																		"##  B#B   BBB D   D    M   M   M M  C###",
																		"# B   BB B B  #   ######################",
																		"###B    B BB  #                    #D###",
																		"##B B BB   #BB#         ]          [ED##",
																		"##C  #B  B    #                    #D###",
																		"########################################",
																	}
	};

};

// Objects Map.
// Initially, the idea was to store the addresses of objects, this would allow us to address them directly.
// But this solution does not allow us to effectively remove objects from the vector (most likely, i just don't know how).
// ??? It may be worth making the Objects Map store the ID of objects in a vector.
// ??? This will allow us to access these elements and work with them at the vector level.
// (It seems to me that the solution is temporary).
// -----------------------------------------------------------------
// As a result, i decided to leave the map of objects, but at the same time remove the vector in principle.

#endif // GAME_H