#pragma once

#define MAP_DEFAULT "Pac-Man"

typedef struct{
	uint scale;
	uint2 len;
	char *name;
	char **tile;
	File file;
}Map;

// screen window pixel to map index
uint stm(const int a)
{
	return a < 0? 0 : a / map->scale;
}

// map index to screen window
uint mts(const int a)
{
	return a < 0? 0 : a * map->scale;
}

void closeMap(Map *map)
{
	if(map == NULL)
		return;
	if(map->name != NULL)
		free(map->name);
	if(map->tile != NULL){
		for(uint i = 0; i < map->len.x; i++)
			free(map->tile[i]);
	}
	free(map->tile);
	free(map);
}

void findMapDimensions(Map *map)
{
	rewind(map->file);
	printf("Finding map dimensions\n");
	int c;

	map->len.x = 0;
	while((c = fgetc(f)) != '\n')
		map->len.x++;

	map->len.y = 1;
	while((c = fgetc(f)) != EOF)
		map->len.y += c=='\n';

	rewind(map->file);
	printf("map dimensions (%02u, %02u)\n", map->len.x, map->len.y);

	map->tile = malloc(sizeof(char*) * map->len.x);
	for(uint i = 0; i < map->len.x; i++)
		map->tile[i] = malloc(sizeof(char) * map->len.y);
}

void parseMapTiles(Map *map)
{
	for(uint y = 0; y < map->len.y; y++){
		for(uint x = 0; x < map->len.x; x++){
			map->tile[x][y] = (char)fgetc(f);
			printf("%c", map->tile[x][y]);
		}
		if(fgetc(f) != '\n'){
			printf("Error parsing map! Expected newline at y = %u\n",y);
			fclose(f);
			exit(0);
		}
		printf("\n");
	}
}

void openMapFile(Map *map)
{
	
}

Map openMap(const char *mapFile)
{
	Map *map = malloc(sizeof(Map));
	printf("Opening map file \"%s\"\n", mapFile);
	map->file = fopen(mapFile, "r");
	if(f == NULL){
		printf("Unable to open map file \"mapFile\"\n");
		printf("Exiting now!\n");
		exit(0);
	}
	map->name = malloc(sizeof(char)*strlen(mapFile)+1);
	strcpy(map->name, mapFile);

	findMapDimensions(map);
	parseMapTiles(map);


	fclose(map->file);
	printf("Loaded map file \"%s\" successfully\n", mapFile);
}

void connectWall(const uint x, const uint y, const Direction dir, bool fill)
{
	const uint wscale = map->scale/3;
	Rect r = {x*map->scale+wscale,y*map->scale+wscale,wscale,wscale};
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
	if(x > 0 && (map->tile[x-1][y] == '#' || map->tile[x-1][y] == 'g'))
		connectWall(x,y,DIR_L, fill);
	if(x < map->len.x-1 && (map->tile[x+1][y] == '#' || map->tile[x+1][y] == 'g'))
		connectWall(x,y,DIR_R, fill);
	if(y > 0 && (map->tile[x][y-1] == '#' || map->tile[x][y-1] == 'g'))
		connectWall(x,y,DIR_U, fill);
	if(x < map->len.y-1 && (map->tile[x][y+1] == '#' || map->tile[x][y+1] == 'g'))
		connectWall(x,y,DIR_D, fill);
}

void drawMap(Map* map)
{
	for(uint y = 0; y < map->len.y; y++){
		for(uint x = 0; x < map->len.x; x++){
			if(map->tile[x][y] == '#'){
				setColor(DARKBLUE);
				drawWall(x,y,true);
			}else if(map->tile[x][y] == 'g'){
				setColor(GREY1);
				drawWall(x,y,true);
			}
		}
	}
	for(uint y = 0; y < map->len.y; y++){
		for(uint x = 0; x < map->len.x; x++){
			switch(map->tile[x][y]){
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
					fillCircle(x*map->scale+map->scale/2, y*map->scale+map->scale/2, map->scale/8);
					break;
				case '@':
					setColor(WHITE);
					fillCircle(x*map->scale+map->scale/2, y*map->scale+map->scale/2, map->scale/3);
					break;
				default:
					break;
			}
		}
	}
}
