#ifndef DUNGEON_H
#define DUNGEON_H

typedef enum{
	WALL,
	ROOM,
	PATH
} TileType;

//TODO: add dungeon tile struct
typedef struct DungeonTile {
	TileType tile;
	//bool occupied;
	//item struct
	//enemy struct
} DungeonTile;

typedef struct Dungeon {
	DungeonTile **layout;
	int width;
	int height;
	int numRooms;
} Dungeon;

Dungeon *generateDungeon(int width, int height, int minRooms, int maxRooms);

void destroyDungeon(Dungeon *d);

void generateRoom(Dungeon *d);

void printDungeon(Dungeon *d);

#endif