#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "dungeon.h"

Dungeon *generateDungeon(int width, int height, int minRooms, int maxRooms){ //rn maxRooms is really maxRooms-1 fyi
	//Making sure shit don't take too long
	time_t start, finish, elapsed;
	
	//TODO: better random num generation
	//setting number of rooms b/t minRooms and maxRooms
	int numRooms = rand() % (maxRooms - minRooms) + minRooms;
	
	//just some info for now
	printf("generateDungeon start:\n");
	printf("width: %d\n", width);
	printf("height: %d\n", height);
	printf("room count: %d\n", numRooms);
	printf("\n");
	
	//allocating memory
	Dungeon *d = (Dungeon*)malloc(sizeof(Dungeon));
	d->layout = (DungeonTile**)malloc(width * sizeof(DungeonTile*));
	for (int i = 0; i < width; i++) {
		d->layout[i] = (DungeonTile*)malloc(height * sizeof(DungeonTile));
	}
	
	//setting dungeon static parameters
	d->width = width;
	d->height = height;
	d->numRooms = numRooms;
	
	//filling dungeon tiles with init values
	for (int w = 0; w < width; w++){
		for (int h = 0; h < height; h++){
			d->layout[w][h].tile = WALL;
		}
	}
	//build rooms
	printf("Building rooms...\n");
	time(&start);
	for (int room = 0; room < numRooms; room++){
		printf("\nBuilding room %d of %d.\n", (room + 1), numRooms);
		generateRoom(d);
		printDungeon(d);
	}
	time(&finish);
	elapsed = finish - start;
	printf("Process finished in %lld seconds.\n", elapsed);
	//TODO: build hallways
	//returning dungeon pointer
	return d;
}

void destroyDungeon(Dungeon *d) {
	free(d);
}

void generateRoom(Dungeon *d) {
	int xcoord, ycoord, roomWidth, roomHeight;
	int minWidth, maxWidth, minHeight, maxHeight, xcoordMin, xcoordMax, ycoordMin, ycoordMax;
	int tryCoords;
	
	//room size ranges
	minWidth = 5;
	minHeight = 5;
	maxWidth = d->width/(d->numRooms-1); //numRooms-1 kinda rando just trying stuff
	maxWidth = maxWidth > minWidth ? maxWidth : minWidth + 3; //ensures max always > min, +3 is just me trying stuff
	maxHeight = d->height/(d->numRooms-1);
	maxHeight = maxHeight > minHeight ? maxHeight : minHeight + 3;
	
	//getting random room dimensions
	PICK_DIMENSIONS:
	roomWidth = rand() % (maxWidth - minWidth) + minWidth;
	roomHeight = rand() % (maxHeight - minHeight) + minHeight;
	
	//coordinate ranges
	xcoordMin = 1;
	ycoordMin = 1;
	xcoordMax = d->width - roomWidth - 1;
	ycoordMax = d->height - roomHeight - 1;
	
	//Variable to ensure program doesn't hang on 'impossible' room
	tryCoords = 0;
	
	//getting random room coordinates
	PICK_COORDS:
	if (tryCoords > 10) goto PICK_DIMENSIONS; //10 might be entirely too low idk
	tryCoords++;
	xcoord = rand() % xcoordMax + xcoordMin;
	ycoord = rand() % ycoordMax + ycoordMin;
	
	//checking if room will be within 4 units of another room
	//the for statements are kinda nasty but they're just deciding on the conditional/starting point to avoid going out of bounds
	for (int w = (xcoord - 4 < 1 ? 1 : xcoord - 4); w < (xcoord + roomWidth + 4 > d->width - 1 ? d->width - 1 : xcoord + roomWidth + 4); w++) {
		for (int h = (ycoord - 4 < 1 ? 1 : ycoord - 4); h < (ycoord + roomHeight + 4 > d->height - 1 ? d->height - 1 : ycoord + roomHeight + 4); h++) {
			if (d->layout[w][h].tile == ROOM) {
				goto PICK_COORDS; //pick some new coords :3c
			}
		}
	}
	//TODO: change room size based on number of rooms and dungeon size
	//TODO: Make it so either generation never hangs, or if it starts hanging make it stop generating and move on
	//either store a variable with total available tiles (so all tiles that are not walls and not near walls or the edge)
	//or be lazy and just break out after enough failed attempts to find a spot for a room
	
	//placing room in dungeon
	for (int w = xcoord; w < xcoord + roomWidth; w++) {
		for (int h = ycoord; h < ycoord + roomHeight; h++) {
			d->layout[w][h].tile = ROOM;
		}
	}
}

void printDungeon(Dungeon *d){
	for (int h = 0; h < d->height; h++) {
		for (int w = 0; w < d->width; w++){
			if(d->layout[w][h].tile == WALL) {
				printf("x ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
}
