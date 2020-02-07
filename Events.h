#pragma once

uint4 key;

struct{
	uint4 x;
	uint4 y;
	char4 keyChar;
}keyLabel = {
	.x = {
		.U = WINX_DEFAULT-(WINX_DEFAULT/10),
		.R = WINX_DEFAULT-(WINX_DEFAULT/10),
		.D = WINX_DEFAULT-(WINX_DEFAULT/10),
		.L = WINX_DEFAULT-(WINX_DEFAULT/10)
	},
	.y = {
		.U = (WINY_DEFAULT/10)*1,
		.R = (WINY_DEFAULT/10)*2,
		.D = (WINY_DEFAULT/10)*3,
		.L = (WINY_DEFAULT/10)*4
	},
	.keyChar = {
		.U = 'U',
		.R = 'R',
		.D = 'D',
		.L = 'L'
	}
};

void keyChange(const Key k, const bool newState)
{
	switch(k){
	case SDLK_ESCAPE:
		printf("Quitting now!\n");
		exit(0);
		break;
	case SDLK_UP:
	case SDLK_w:
		key.U = newState;
		break;
	case SDLK_DOWN:
	case SDLK_s:
		key.D = newState;
		break;
	case SDLK_LEFT:
	case SDLK_a:
		key.L = newState;
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		key.R = newState;
		break;
	default:
		printf("Unknown key pressed.\n");
		break;
	}
}

void events()
{
	static SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_QUIT:
			printf("Quitting now!\n");
			exit(0);
			break;
		case SDL_KEYDOWN:
			if(!event.key.repeat)
				keyChange(event.key.keysym.sym, true);
			break;
		case SDL_KEYUP:
			keyChange(event.key.keysym.sym, false);
			break;
		default:
			break;
		}
	}
	clearTerminal();
	printf("Key %c %+4u.\n", keyLabel.keyChar.U, key.U);
	printf("Key %c %+4u.\n", keyLabel.keyChar.D, key.D);
	printf("Key %c %+4u.\n", keyLabel.keyChar.L, key.L);
	printf("Key %c %+4u.\n", keyLabel.keyChar.R, key.R);
	if(key.U)
		key.U = (key.U+1)%1000;
	if(key.D)
		key.D = (key.D+1)%1000;
	if(key.L)
		key.L = (key.L+1)%1000;
	if(key.R)
		key.R = (key.R+1)%1000;
}
