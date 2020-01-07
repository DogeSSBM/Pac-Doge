#define DOGE_GFX
#include "Includes.h"

int main(int argc, char const *argv[])
{
	switch(argc){
		case 3:
			map.scale = strToInt(argv[2]);
			// fallthrough
		case 2:
			openMap(argv[1]);
			break;
		default:
			map.scale = 32;
			openMap("map");
			break;
	}
	init(map.scale*map.xlen,map.scale*map.ylen);
	while(1){
		drawMap();
		draw();
		events();
	}
	closeMap();
	return 0;
}
