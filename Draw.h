#pragma once

typedef enum{DIR_U, DIR_D, DIR_L, DIR_R}Dir;

typedef struct{

}Wall;

void drawStraightWall(int x, int y, Dir offset)
{

	switch (offset) {
	case DIR_U:
		y-=4;
		break;
	case DIR_D:
		y+=4;
		break;
	case DIR_L:
		x-=4;
		break;
	case DIR_R:
		x+=4;
		break;
	}

}
