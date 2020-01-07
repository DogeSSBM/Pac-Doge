#pragma once

#define MAP_DEFAULT "Pac-Man"

struct{
	uint scale;
	uint xlen;
	uint ylen;
	char **tile;
}map;

void closeMap(void)
{
	if(map.tile == NULL)
		return;
	for(uint i = 0; i < map.xlen; i++){
		free(map.tile[i]);
	}
	free(map.tile);
	// map.scale = 0;
	map.xlen = 0;
	map.ylen = 0;
	map.tile = NULL;
}

void openMap(const char *mapFile)
{
	if(map.tile != NULL){
		printf("Closing current map\n");
		closeMap();
	}
	printf("Opening map file \"mapFile\"\n");
	File *f = fopen(mapFile, "r");
	if(f == NULL){
		printf("Unable to open map file \"mapFile\"\n");
		printf("Exiting now!\n");
		exit(0);
	}
	printf("Finding map dimensions\n");
	int c;
	map.xlen = 0;
	while((c = fgetc(f)) != '\n'){
		map.xlen++;
	}
	map.ylen = 1;
	while((c = fgetc(f)) != EOF){
		map.ylen += c=='\n';
	}
	rewind(f);
	printf("map dimensions (%02u, %02u)\n", map.xlen, map.ylen);

	map.tile = malloc(sizeof(char*) * map.xlen);
	for(uint i = 0; i < map.xlen; i++){
		map.tile[i] = malloc(sizeof(char) * map.ylen);
	}
	for(uint y = 0; y < map.ylen; y++){
		for(uint x = 0; x < map.xlen; x++){
			map.tile[x][y] = (char)fgetc(f);
			printf("%c", map.tile[x][y]);
		}
		if(fgetc(f) != '\n'){
			printf("Error parsing map! Expected newline at y = %u\n",y);
			fclose(f);
			exit(0);
		}
		printf("\n");
	}
	fclose(f);
}

void connectWall(const uint x, const uint y, const Direction dir, bool fill)
{
	const uint wscale = map.scale/3;
	Rect r = {x*map.scale+wscale,y*map.scale+wscale,wscale,wscale};
	switch(dir){
		case DIR_U:
			r.y-=wscale;
			// fallthrough
		case DIR_D:
			r.h+=wscale;
			break;
		case DIR_L:
			r.x-=wscale;
			// fallthrough
		case DIR_R:
			r.w+=wscale;
			break;
		default:
			break;
	}
	if(fill)
		fillRect(r.x,r.y,r.w,r.h);
	else
		drawRect(r.x,r.y,r.w,r.h);
}

void drawWall(uint x, uint y, bool fill)
{
	if(x > 0 && (map.tile[x-1][y] == '#' || map.tile[x-1][y] == 'g'))
		connectWall(x,y,DIR_L, fill);
	if(x < map.xlen-1 && (map.tile[x+1][y] == '#' || map.tile[x+1][y] == 'g'))
		connectWall(x,y,DIR_R, fill);
	if(y > 0 && (map.tile[x][y-1] == '#' || map.tile[x][y-1] == 'g'))
		connectWall(x,y,DIR_U, fill);
	if(x < map.ylen-1 && (map.tile[x][y+1] == '#' || map.tile[x][y+1] == 'g'))
		connectWall(x,y,DIR_D, fill);
}

void drawMap(void)
{
	for(uint y = 0; y < map.ylen; y++){
		for(uint x = 0; x < map.xlen; x++){
			if(map.tile[x][y] == '#'){
				setColor(DARKBLUE);
				drawWall(x,y,true);
			}else if(map.tile[x][y] == 'g'){
				setColor(GREY1);
				drawWall(x,y,true);
			}
		}
	}
	for(uint y = 0; y < map.ylen; y++){
		for(uint x = 0; x < map.xlen; x++){
			switch(map.tile[x][y]){
				case '#':
					setColor(BLUE);
					drawWall(x, y, false);
					break;
				case 'g':
					setColor(WHITE);
					drawWall(x, y, false);
					break;
				case '.':
					setColor(WHITE);
					fillCircle(x*map.scale+map.scale/2, y*map.scale+map.scale/2, map.scale/8);
					break;
				case '@':
					setColor(WHITE);
					fillCircle(x*map.scale+map.scale/2, y*map.scale+map.scale/2, map.scale/3);
					break;
				default:
					break;
			}
		}
	}
}
