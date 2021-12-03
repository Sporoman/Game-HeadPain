#pragma once

// This file is a temporary solution

#include "consoleColor//ConsoleColor.h"
#include "Object.h"
#include "Hero.h"
#include <vector>
#include <memory>
namespace game_info
{
	std::vector<Object> objects;
	Hero hero(2, ccolor::Color::green, Coord{ 0,0 });

	static unsigned int level = 0;
	static unsigned int CrystalScore = 0;
	static unsigned int CrystalScoreCollected = 0;
	static unsigned int CrystalScoreONLVL = 0;
	static unsigned int KeyScore = 0;
	static unsigned int KeyScoreLVL = 0;
	static unsigned int LevelKeyScore = 0;

	const unsigned char mapSymbol_fogOfWar = 176;
	const unsigned char mapSymbol_empty = ' ';
	const unsigned char mapSymbol_hero = 'H';
	const unsigned char mapSymbol_wall = '#';
	const unsigned char mapSymbol_door = 'D';
	const unsigned char mapSymbol_levelDoor = '[';
	const unsigned char mapSymbol_key = 'K';
	const unsigned char mapSymbol_levelKey = ']';
	const unsigned char mapSymbol_box = 'B';
	const unsigned char mapSymbol_exit = 'E';
	const unsigned char mapSymbol_crystal = 'C';
	const unsigned char mapSymbol_mine = 'M';

	const int y_size_lvl = 21;
	const int x_size_lvl = 40;
	const int levelsCount = 7;
	const unsigned char levelsData[levelsCount][y_size_lvl][x_size_lvl + 1] = {
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

	enum class Entity
	{
		empty,
		wall,
		door,
		levelDoor,
		key,
		levelKey,
		box,
		exitDoor,
		crystal,
		mine
	};

	Object CreateObject(unsigned char symbol)
	{
		unsigned char mapSym   = symbol;
		unsigned char renSym   = GetRenderCellSymbol(symbol);
		ccolor::Color colorSym = GetRenderCellSymbolColor(symbol);

		return Object(mapSym, renSym, colorSym);
	}

	static unsigned char GetRenderCellSymbol(unsigned char symbol)
	{
		switch (symbol)
		{
			case mapSymbol_empty:		return ' ';
			case mapSymbol_hero:		return 2;
			case mapSymbol_wall:		return 177;
			case mapSymbol_door:        return 219;
			case mapSymbol_levelDoor:   return 219;
			case mapSymbol_key:			return 21;
			case mapSymbol_levelKey:	return 21;
			case mapSymbol_box:			return 254;
			case mapSymbol_exit:		return 176;
			case mapSymbol_crystal:		return 4;
			case mapSymbol_mine:		return 15;
		}

		return '?';
	}

	static ccolor::Color GetRenderCellSymbolColor(unsigned char symbol)
	{
		switch (symbol)
		{
			case mapSymbol_empty:		return ccolor::Color::black;
			case mapSymbol_hero:		return ccolor::Color::green;
			case mapSymbol_wall:		return ccolor::Color::white;
			case mapSymbol_door:		return ccolor::Color::yellow;
			case mapSymbol_levelDoor:	return ccolor::Color::blue;
			case mapSymbol_key:			return ccolor::Color::cyan;
			case mapSymbol_levelKey:	return ccolor::Color::blue;
			case mapSymbol_box:			return ccolor::Color::brown;
			case mapSymbol_exit:		return ccolor::Color::magenta;
			case mapSymbol_crystal:		return ccolor::Color::magenta;
			case mapSymbol_mine:		return ccolor::Color::red;
		}

		return ccolor::Color::gray;
	}
}