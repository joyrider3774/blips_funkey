#ifndef DEFINES_H
#define DEFINES_H


#define ORIG_WINDOW_WIDTH 240
#define ORIG_WINDOW_HEIGHT 240 
#define TileWidth 16
#define TileHeight 16
#define SCREEN_BPP 16
#define FPS 60
#define UI_WIDTH_SCALE 0.75
#define UI_HEIGHT_SCALE 1

#define AlphaInc 5
#define NrOfRows 50
#define NrOfCols 50
#define NrOfColsVisible ((ORIG_WINDOW_WIDTH / TileWidth))
#define NrOfRowsVisible ((ORIG_WINDOW_HEIGHT / TileHeight))
#define IDEmpty 1
#define IDPlayer 2
#define IDBox 3
#define IDFloor 4
#define IDBomb 5
#define IDWall 6
#define IDDiamond 7
#define IDExplosion 8
#define ZPlayer 10
#define ZDiamond 3
#define ZWall 5
#define ZBox 5
#define ZBomb 3
#define ZFloor 1
#define ZExplosion 15
#define MaxLevelPacks 200
#define MaxMusicFiles 26
#define NrOfSounds 7
#define SND_MENU 0
#define SND_SELECT 1
#define SND_ERROR 2
#define SND_STAGEEND 3
#define SND_EXPLODE 4
#define SND_COLLECT 5
#define SND_BACK 6
#define MaxAlpha 150
#define InputDelay 13

#define NROFBUTTONS 14
#define BUT_UP 0
#define BUT_RIGHT 1
#define BUT_DOWN 2
#define BUT_LEFT 3
#define BUT_A 4
#define BUT_X 5
#define BUT_Y 6
#define BUT_B 7
#define BUT_START 8
#define BUT_SELECT 9
#define BUT_L 10
#define BUT_R 11
#define BUT_VOLMIN 12
#define BUT_VOLUP 13

#endif