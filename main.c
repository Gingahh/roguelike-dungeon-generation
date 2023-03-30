#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "dungeon.h"

int main() {
	srand(time(NULL));
	int playing = 1;
	Dungeon *dungeon = generateDungeon(50, 40, 3, 13);
	printf("\nFinal Dungeon Layout:\n");
	printDungeon(dungeon);
	printf("\nPROGRAM FINISHED SUCCESSFULLY\n");
	while(playing);
	return 0;
}