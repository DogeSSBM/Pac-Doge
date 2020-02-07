#pragma once

int setClipboard(char *text)
{
	return SDL_SetClipboardText(text);
}

char* getClipboard(void)
{
	return SDL_GetClipboardText();
}

void clearTerminal(void)
{
	printf("\e[1;1H\e[2J");
}

float randRange(float a, float b)
{
	return ((b-a)*((float)rand()/RAND_MAX))+a;
}
