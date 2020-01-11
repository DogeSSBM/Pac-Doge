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

void printOnceAtAlligned(Entity *e)
{
	static bool lastaligned = false;
	if(aligned(e->x,e->y)){
		if(!lastaligned)
			printf("Aligned at (%02u, %02u)\n", stm(e->x), stm(e->y));
		lastaligned = true;
	}else{
		lastaligned = false;
	}
}

bool traversable(const uint x, const uint y)
{
	return map.tile[x][y] != '#' && map.tile[x][y] != 'g';
}

void turnEntity(Entity *e)
{
	// reverse if needed
	switch(e->facing) {
		case DIR_U:
			if(keyState.inverse.U && !keyState.U){
				e->facing = (e->facing+2)%4;
				break;
			}
			break;
		case DIR_R:
			if(keyState.inverse.R && !keyState.R){
				e->facing = (e->facing+2)%4;
				break;
			}
			break;
		case DIR_D:
			if(keyState.inverse.D && !keyState.D){
				e->facing = (e->facing+2)%4;
				break;
			}
			break;
		case DIR_L:
			if(keyState.inverse.L && !keyState.L){
				e->facing = (e->facing+2)%4;
				break;
			}
			break;
	}

	// turn at perp aligned points if needed
	if(!aligned(e->x,e->y))
		return;

	uint newx = e->x;
	uint newy = e->y;
	if(UD(e->facing)){
		if(keyState.L && !keyState.inverse.L){
			newx--;
			e->turn = DIR_L;
		}else if(keyState.R){
			newx+=map.scale;
			e->turn = DIR_R;
		}else{
			return;
		}
	}else{
		if(keyState.U && !keyState.inverse.U){
			newy--;
			e->turn = DIR_U;
		}else if(keyState.D){
			newy+=map.scale;
			e->turn = DIR_D;
		}else{
			return;
		}
	}

	if(!traversable(stm(newx),stm(newy)))
		return;
	e->facing = e->turn;
}

void moveEntity(Entity *e)
{
	printOnceAtAlligned(e);
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
