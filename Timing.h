#pragma once

const u32 frameTime = 1000 / 120;
u32 startTime;

void markStartTime(void)
{
	startTime = SDL_GetTicks();
}

u32 elapsedTime(void)
{
	return SDL_GetTicks() - startTime;
}

u32 remainingTime(void)
{
	u32 eTime = elapsedTime();
	return eTime > frameTime ? 0 : frameTime - eTime;
}
