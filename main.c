#define DOGE_GFX
#define SCALE_DEFAULT 32
#include "Includes.h"

int main(int argc, char const *argv[])
{
	gfx_init(WINX_DEFAULT, WINY_DEFAULT);
	img_init();
	text_init();
	uint x = 0;
	while(1){
		Epoch frameStart = getEpoch();

		setColor(BLACK);
		fillCircle(x, 300, 100);

		x = (x+1)%800;

		setColor(RED);
		fillCircle(x, 300, 100);

		events();
		draw();
		while(timeSince(frameStart) < FRAMETIME);
	}
	return 0;
}
