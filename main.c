#include "Includes.h"

int main(int argc, char const *argv[])
{
	init_all(1200, 600);
	fillScreen();
	const char* sprites[] = {
		"assets/doge0r.png",	"assets/doge0l.png",
		"assets/doge0u.png",	"assets/doge0d.png",
		"assets/doge1r.png",	"assets/doge1l.png",
		"assets/doge1u.png",	"assets/doge1d.png",
		"assets/dot0.png",	"assets/dot1.png",
		"assets/wHs.png",		"assets/wVs.png",
		"assets/wHdu.png",	"assets/wHdd.png",
		"assets/wVdl.png",	"assets/wVdr.png",
		"assets/wLs0.png",	"assets/wLs1.png",
		"assets/wLs2.png",	"assets/wLs3.png",
		"assets/wLd0.png",	"assets/wLd1.png",
		"assets/wLd2.png",	"assets/wLd3.png",
	};
	for(uint i = 0; i < 12; i++){
		loadDrawImg(sprites[i], 64*i+i*16, 0, 64, 64);
		loadDrawImg(sprites[i+12], 64*i+i*16, 64+16, 64, 64);
	}
	draw();
	while(1){
		events();
		delay(4);
	}
}
