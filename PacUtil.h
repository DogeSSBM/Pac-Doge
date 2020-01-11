#pragma once

void parseArgs(int argc, char const *argv[])
{
	map.scale = 32;
	switch(argc){
		case 3:
			map.scale = strToInt(argv[2]);
			// fallthrough
		case 2:
			openMap(argv[1]);
			return;
			break;
		default:
			openMap(MAP_DEFAULT);
			return;
			break;
	}
}
