#include "Includes.h"

int main(int argc, char const *argv[])
{
	init_all(800, 600);
	fillScreen();
	const char* sprites[] = {
		"assets/doge0.png",	"assets/doge1.png",
		"assets/dot0.png",	"assets/dot1.png",
		"assets/w0s.png",		"assets/w0d.png",
		"assets/w1s.png",		"assets/w1d.png"
	};
	for(uint i = 0; i < 8; i++){
		loadDrawImg(sprites[i], 64*i, 0, 64, 64);
	}
	draw();
	while(1){
		events();
		delay(4);
	}
}
