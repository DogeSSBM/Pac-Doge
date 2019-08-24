#pragma once

typedef enum{DIR_R, DIR_D, DIR_L, DIR_U}Dir;
typedef enum{C_INNER, C_OUTER}CornerType;

typedef struct{
	int xoffset, yoffset;
	Img* sprite;
}Wall;

Wall wall[4];
Wall wallDouble[4];
Wall cornerInner[4];
Wall cornerInnerDouble[4];
Wall cornerOuter[4];
Wall cornerOuterDouble[4];

Img *loadWalls(void){
	wall[0].sprite  = loadImg("./assets/wVs.png");
	wall[0].xoffset =  SCALE;
	wall[0].yoffset =  0;
	wallDouble[0].sprite  = loadImg("./assets/wVd.png");
	wallDouble[0].xoffset =  SCALE;
	wallDouble[0].yoffset =  0;

	wall[1].sprite  = loadImg("./assets/wHs.png");
	wall[1].xoffset =  0;
	wall[1].yoffset =  SCALE;
	wallDouble[1].sprite  = loadImg("./assets/wHd.png");
	wallDouble[1].xoffset =  0;
	wallDouble[1].yoffset =  SCALE;

	wall[2].sprite  = loadImg("./assets/wVs.png");
	wall[2].xoffset = -SCALE;
	wall[2].yoffset =  0;
	wallDouble[2].sprite  = loadImg("./assets/wVd.png");
	wallDouble[2].xoffset = -SCALE;
	wallDouble[2].yoffset =  0;

	wall[3].sprite  = loadImg("./assets/wHs.png");
	wall[3].xoffset =  0;
	wall[3].yoffset = -SCALE;
	wallDouble[3].sprite  = loadImg("./assets/wHd.png");
	wallDouble[3].xoffset =  0;
	wallDouble[3].yoffset = -SCALE;
}

void drawWall(int x, int y, Dir offset)
{
	setColor(BLUE);
	drawImg(wall[offset].sprite, (x+wall[offset].xoffset)*SCALE, (y+wall[offset].yoffset)*SCALE, SCALE, SCALE);
}
