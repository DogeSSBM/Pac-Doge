#pragma once

void handleKey(Key k)
{
	switch (k)
	{
	case SDLK_ESCAPE:
		printf("Quitting now!\n");
		exit(0);
		break;
	case SDLK_UP:
		printf("UP key pressed.\n");
		break;
	case SDLK_DOWN:
		printf("DOWN key pressed.\n");
		break;
	case SDLK_LEFT:
		printf("LEFT key pressed.\n");
		break;
	case SDLK_RIGHT:
		printf("RIGHT key pressed.\n");
		break;
	}
}

void events()
{
	markStartTime();
	SDL_Event event;
	while (SDL_WaitEventTimeout(&event, remainingTime()))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			printf("Quitting now!\n");
			exit(0);
			break;
		case SDL_KEYDOWN:
			handleKey(event.key.keysym.sym);
			break;
		default:
			break;
		}
	}
	draw();
}
