#pragma once
#define KEYNUM 4

struct{
	bool U;
	bool D;
	bool L;
	bool R;
}key;

void keyDown(const Key k, const bool state)
{
	printf("Key %1u %c\n", (uint)k, state?'1':'0');
	switch(k)
	{
	case SDLK_ESCAPE:
		printf("Quitting now!\n");
		exit(0);
		break;
	case SDLK_w:
	case SDLK_UP:
		key.U = state;
		break;
	case SDLK_s:
	case SDLK_DOWN:
		key.D = state;
		break;
	case SDLK_a:
	case SDLK_LEFT:
		key.L = state;
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		key.R = state;
		break;
	default:
		printf("OTHER key pressed.\n");
		break;
	}
}



void events()
{
	markStartTime();
	SDL_Event event;
	while (SDL_WaitEventTimeout(&event, remainingTime()))
	{
		bool state = true;
		switch (event.type)
		{
		case SDL_QUIT:
			printf("Quitting now!\n");
			exit(0);
			break;
		case SDL_KEYUP:
			state = false;
		case SDL_KEYDOWN:
			if(event.key.repeat == 0)
				keyDown(event.key.keysym.sym, state);
			break;
		// case SDL_KEYUP:
		// 	keyUp(event.key.keysym.sym);
		// 	break;
		default:
			break;
		}
	}
	draw();
}
