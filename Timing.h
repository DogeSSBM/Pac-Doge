#pragma once
#define FPS		60
#define FRAMETIME	(1000/FPS)

Epoch getEpoch(void)
{
	return SDL_GetTicks();
}

u32 timeSince(Epoch e)
{
	return SDL_GetTicks() - e;
}
