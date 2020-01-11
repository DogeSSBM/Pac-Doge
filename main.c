#define DOGE_GFX
#include "Includes.h"

int main(int argc, char const *argv[])
{
	parseArgs(argc, argv);
	init(map.scale*map.xlen,map.scale*map.ylen);
	initEntity();
	while(1){
		moveEntity(&player);
		clear();
		drawMap();
		drawEntity(&player);
		draw();
		events();
	}
	closeMap();
	return 0;
}
