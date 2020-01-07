#define DOGE_GFX
#include "Includes.h"

int main(int argc, char const *argv[])
{
	parseArgs(argc, argv);
	init(map.scale*map.xlen,map.scale*map.ylen);
	while(1){
		drawMap();
		draw();
		events();
	}
	closeMap();
	return 0;
}
