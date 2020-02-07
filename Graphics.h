#pragma once
#define WINX_DEFAULT (SCALE_DEFAULT*28)
#define WINY_DEFAULT (SCALE_DEFAULT*31)

struct{
	uint xlen, ylen;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	int fontSize;
	Color fontColor;
	Color defaultColor;
}gfx = {};

typedef enum{
	BLEND_NONE	= SDL_BLENDMODE_NONE,
	BLEND_ALPHA	= SDL_BLENDMODE_BLEND,
	BLEND_ADD	= SDL_BLENDMODE_ADD,
	BLEND_MOD	= SDL_BLENDMODE_MOD
}BlendMode;

typedef enum{
	FULLSCREEN	= SDL_WINDOW_FULLSCREEN,
	BORDERLESS	= SDL_WINDOW_FULLSCREEN_DESKTOP,
	WINDOWED	= 0
}WindowMode;

void setWindowMode(const WindowMode mode)
{
	SDL_SetWindowFullscreen(gfx.window, mode);
}

void setWindowSize(const uint x, const uint y)
{
	gfx.xlen = x;
	gfx.ylen = y;
	SDL_SetWindowSize(gfx.window, x, y);
}

void setBlend(const BlendMode mode)
{
	SDL_SetRenderDrawBlendMode(gfx.renderer, mode);
}

void drawPixel(const uint x, const uint y)
{
	SDL_RenderDrawPoint(gfx.renderer, x, y);
}

void drawLine(const uint x1, const uint y1, const uint x2, const uint y2)
{
	SDL_RenderDrawLine(gfx.renderer, x1, y1, x2, y2);
}

void drawHLine(const uint x, const uint y, const int len)
{
	SDL_RenderDrawLine(gfx.renderer, x, y, x+len, y);
}

void drawVLine(const uint x, const uint y, const int len)
{
	SDL_RenderDrawLine(gfx.renderer, x, y, x, y+len);
}

void drawRect(const uint x, const uint y, const uint xlen, const uint ylen)
{
	Rect r = {x, y, xlen, ylen};
	SDL_RenderDrawRect(gfx.renderer, &r);
}

void fillRect(const uint x, const uint y, const uint xlen, const uint ylen)
{
	Rect r = {x, y, xlen, ylen};
	SDL_RenderFillRect(gfx.renderer, &r);
}

void drawSquare(const uint x, const uint y, const uint len)
{
	Rect r = {x, y, len, len};
	SDL_RenderDrawRect(gfx.renderer, &r);
}

void fillSquare(const uint x, const uint y, const uint len)
{
	Rect r = {x, y, len, len};
	SDL_RenderFillRect(gfx.renderer, &r);
}

void fillBorder(const uint x, const uint y, const uint xlen, const uint ylen, const int b)
{
	fillRect(x-b, y-b, xlen+2*b, b);
	fillRect(x-b, y+ylen, xlen+2*b, b);
	fillRect(x-b, y, b, ylen);
	fillRect(x+xlen, y, b, ylen);
}

void drawCircle(const uint x, const uint y, const uint radius)
{
	const uint rsq = radius*radius;
	uint yoff = radius;
	for(uint xoff = 0; xoff <= yoff; xoff++){
		double yc = sqrt(rsq - (xoff+1)*(xoff+1));
		double ym = (double)yoff - 0.5;
		// 8 sections of circle
		drawPixel(x+xoff, y+yoff);		// 1
		drawPixel(x-yoff, y+xoff);		// 2
		drawPixel(x-xoff, y-yoff);		// 3
		drawPixel(x+yoff, y-xoff);		// 4

		drawPixel(x-xoff, y+yoff);		// 5
		drawPixel(x-yoff, y-xoff);		// 6
		drawPixel(x+xoff, y-yoff);		// 7
		drawPixel(x+yoff, y+xoff);		// 8
		yoff -= yc <= ym;
	}
}

void fillCircle(const uint x, const uint y, const uint radius)
{
	const uint rsq = radius*radius;
	uint yoff = radius;
	for(uint xoff = 0; xoff <= yoff; xoff++){
		double yc = sqrt(rsq - (xoff+1)*(xoff+1));
		double ym = (double)yoff - 0.5;
		// connecting 8 sections of circle
		drawLine(x+xoff, y-yoff, x+xoff, y+yoff);		// 7 to 1
		drawLine(x-yoff, y+xoff, x+yoff, y+xoff);		// 2 to 8
		drawLine(x-xoff, y-yoff, x-xoff, y+yoff);		// 3 to 5
		drawLine(x-yoff, y-xoff, x+yoff, y-xoff);		// 6 to 4
		yoff -= yc <= ym;
	}
}

void setColor(const Color c)
{
	SDL_SetRenderDrawColor(gfx.renderer, c.r, c.g, c.b, c.a);
}

void setRGB(const u8 r, const u8 g, const u8 b)
{
	SDL_SetRenderDrawColor(gfx.renderer, r, g, b, 255);
}

void setRGBA(const u8 r, const u8 g, const u8 b, const u8 a)
{
	SDL_SetRenderDrawColor(gfx.renderer, r, g, b, a);
}

void blank()
{
	setColor(gfx.defaultColor);
	SDL_RenderClear(gfx.renderer);
	fillRect(0,0,gfx.xlen,gfx.ylen);
}

void draw()
{
	SDL_RenderPresent(gfx.renderer);
}

void saveScreenshot(const char* file_name)
{
	SDL_Surface *sshot = SDL_CreateRGBSurface(0, gfx.xlen, gfx.ylen, 32,
		0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(gfx.renderer, NULL, SDL_PIXELFORMAT_ARGB8888,
		sshot->pixels, sshot->pitch);
	SDL_SaveBMP(sshot, file_name);
	//SDL_FreeSurface(sshot);
}

void gfx_quit(void)
{
	// Destroy renderer
	SDL_DestroyRenderer(gfx.renderer);
	// Destroy window
	SDL_DestroyWindow(gfx.window);
	// Quit SDL subsystems
	SDL_Quit();
}

void gfx_init(const uint winXlen, const uint winYlen)
{
	srand(time(NULL));
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL borked! Error: %s\n", SDL_GetError());
		exit(0);
	}
	else{
		//Create window
		SDL_CreateWindowAndRenderer(winXlen, winYlen, 0,
			&(gfx.window), &(gfx.renderer));
		printf("Adding gfx_quit to atexit()\n");
		atexit(gfx_quit);
		gfx.xlen = winXlen;
		gfx.ylen = winYlen;
		gfx.defaultColor = BLACK;
		SDL_SetRenderDrawBlendMode(gfx.renderer, SDL_BLENDMODE_BLEND);
		blank();
		draw();
		blank();
	}
}
