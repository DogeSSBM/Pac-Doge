#pragma once
#define KEYNUM 4

const union{
	char arr[KEYNUM];
	struct{
		char U;
		char R;
		char D;
		char L;
	};
}keyLabel = {'U','R','D','L'};

union{
	struct{
		bool U;
		bool R;
		bool D;
		bool L;
	};
	struct{
		bool D;
		bool L;
		bool U;
		bool R;
	}inverse;
}keyState={0};

void keyDown(const Key k, const bool state)
{
	switch(k)
	{
	case SDLK_ESCAPE:
		printf("Quitting now!\n");
		exit(0);
		break;
	case SDLK_w:
	case SDLK_UP:
		keyState.U = state;
		printf("Key %c = %c\n",keyLabel.U,state?'1':'0');
		break;
	case SDLK_s:
	case SDLK_DOWN:
		keyState.D = state;
		printf("Key %c = %c\n",keyLabel.D,state?'1':'0');
		break;
	case SDLK_a:
	case SDLK_LEFT:
		keyState.L = state;
		printf("Key %c = %c\n",keyLabel.L,state?'1':'0');
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		keyState.R = state;
		printf("Key %c = %c\n",keyLabel.R,state?'1':'0');
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
