#pragma once

void parseArgs(int argc, char const *argv[])
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
			openMap(MAP_DEFAULT);
			break;
	}
}
