#pragma once

// This file is a temporary solution

#include "Object.h"
#include "Hero.h"
#include "renderSystem/renderSystem.h"

static Hero* hero = new Hero();
static RenderSystem renderSys;

static unsigned int level = 0;
static unsigned int CrystalScoreCollected = 0;
static unsigned int CrystalScoreONLVL = 0;
static unsigned int KeyScoreCollected = 0;
static unsigned int KeyScoreONLVL = 0;

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