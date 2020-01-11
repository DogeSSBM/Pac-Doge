#pragma once

#define UD(d)	(~(d)&1)
#define LR(d)	( (d)&1)

typedef enum{ENT_NONE = 0, ENT_GHOST, ENT_PLAYER}EntityType;
typedef struct{
	EntityType type;
	uint x, y;
	Color color;
	Direction facing;
	Direction turn;		// buffered turn direction
}Entity;

Entity ghosts[4];
Entity player;

void initEntity()
{
	player.type = ENT_PLAYER;
	player.x = mts(13);
	player.y = mts(23);
	player.color = YELLOW;
	player.facing = DIR_L;
	player.turn = DIR_L;
}

void drawEntity(Entity *e)
{
	setColor(e->color);
	fillCircle(e->x+map.scale/2, e->y+map.scale/2, map.scale/2);
}

bool aligned(const uint x, const uint y)
{
	return x % map.scale == 0 && y % map.scale == 0;
}

bool traversable(const uint x, const uint y)
{
	return map.tile[x][y] != '#' && map.tile[x][y] != 'g';
}

void turnEntity(Entity *e)
{
	uint newx = stm(e->x);
	uint newy = stm(e->y);
	switch(e->turn) {
		case DIR_U:
			newy--;
			printf("Turn U to (%02u,%02u)", newx, newy);
			break;
		case DIR_R:
			newx++;
			printf("Turn R to (%02u,%02u)", newx, newy);
			break;
		case DIR_D:
			newy++;
			printf("Turn D to (%02u,%02u)", newx, newy);
			break;
		case DIR_L:
			newx--;
			printf("Turn L to (%02u,%02u)", newx, newy);
			break;
	}
	if(traversable(newx,newy)){
		e->facing = e->turn;
		printf(" success\n");
	}else{
		printf(" failure\n");
	}
}

void moveEntity(Entity *e)
{
	static bool lastaligned = false;
	if(aligned(e->x,e->y)){
		if(!lastaligned)
			printf("Alligned at (%02u, %02u)\n", stm(e->x), stm(e->y));
		lastaligned = true;
	}else{
		lastaligned = false;
	}

	if(e->facing != e->turn)
		turnEntity(e);
	uint newx = e->x;
	uint newy = e->y;
	switch(e->facing) {
		case DIR_U:
			newy--;
			break;
		case DIR_R:
			newx++;
			newx+=map.scale-1;
			break;
		case DIR_D:
			newy++;
			newy+=newx+=map.scale-1;
			break;
		case DIR_L:
			newx--;
			break;
	}
	if(traversable(stm(newx), stm(newy))){
		switch(e->facing) {
			case DIR_U:
				e->y--;
				break;
			case DIR_R:
				e->x++;
				break;
			case DIR_D:
				e->y++;
				break;
			case DIR_L:
				e->x--;
				break;
		}
	}
}
