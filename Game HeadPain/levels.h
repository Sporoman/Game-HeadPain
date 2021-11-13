#pragma once
#include "consoleColor//ConsoleColor.h"

static unsigned int level = 0;
static unsigned int CrystalScore = 0;
static unsigned int CrystalScoreLVL = 0;
static unsigned int CrystalScoreONLVL = 0;
static unsigned int KeyScore = 0;
static unsigned int KeyScoreLVL = 0;
static unsigned int LevelKeyScore = 0;

const unsigned char fogOfWar = 176;
const unsigned char Void = ' ';
const unsigned char Hero = 'H';
const unsigned char Wall = '#';
const unsigned char Door = 'D';
const unsigned char LevelDoor = '[';
const unsigned char Key = 'K';
const unsigned char LevelKey = ']';
const unsigned char Box = 'B';
const unsigned char Exit = 'E';
const unsigned char Crystal = 'C';
const unsigned char Mine = 'M';

const int rowsCount = 21;
const int columnsCount = 40;
const int levelsCount = 7;
const unsigned char levelsData[levelsCount][rowsCount][columnsCount + 1] = {
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


static unsigned char GetRenderCellSymbol(unsigned char symbol)
{
	switch (symbol)
	{
		case Void:			return ' ';
		case Hero:			return 2;
		case Wall:			return 177;
		case Door:			return 219;
		case LevelDoor:		return 219;
		case Key:			return 21;
		case LevelKey:		return 21;
		case Box:			return 254;
		case Exit:			return 176;
		case Crystal:		return 4;
		case Mine:			return 15;
	}

	return '?';
}

static ccolor::Color GetRenderCellSymbolColor(unsigned char symbol)
{
	switch (symbol)
	{
		case Void:			return ccolor::Color::black;
		case Hero:			return ccolor::Color::green;
		case Wall:			return ccolor::Color::white;
		case Door:			return ccolor::Color::yellow;
		case LevelDoor:		return ccolor::Color::blue;
		case Key:			return ccolor::Color::cyan;
		case LevelKey:		return ccolor::Color::blue;
		case Box:			return ccolor::Color::brown;
		case Exit:			return ccolor::Color::magenta;
		case Crystal:		return ccolor::Color::magenta;
		case Mine:			return ccolor::Color::red;
	}

	return ccolor::Color::gray;
}
