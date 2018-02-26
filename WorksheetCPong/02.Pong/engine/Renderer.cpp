#include "Renderer.h"

int RGBATOCOLOR(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return b | (g << 8) | (r << 16) | (a << 24);
}

void COLORTORGBA(int col, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a)
{
	r = (col & 0x00ff0000) >> 16;
	g = (col & 0x0000ff00) >> 8;
	b = (col & 0x000000ff);
	a = (col & 0xff000000) >> 24;
}


int RGBTOCOLOR(unsigned char r, unsigned char g, unsigned char b)
{
	return RGBATOCOLOR(r, g, b, 255);
}


int SDLCALL watch(void *userdata, SDL_Event* event)
{

	if (event->type == SDL_APP_WILLENTERBACKGROUND)
	{
		//quitting = true;
	}

	return 1;
}

bool Renderer::OnStartUp()
{
	window = NULL;
	renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	debugPrinter = new DebugPrinter();
	debugPrinter->Init();

	SDL_AddEventWatch(watch, NULL);


	return true;
}

void Renderer::DrawRect(float x, float y, float w, float h, u32 col)
{
	SDL_Rect rect;

	rect.x = (s32)x;
	rect.y = (s32)y;
	rect.w = (s32)w;
	rect.h = (s32)h;

	unsigned char r, g, b, a;

	COLORTORGBA(col, r, g, b, a);


	SDL_SetRenderDrawColor(renderer, r,g,b,a);
	SDL_RenderFillRect(renderer, &rect);

}

void Renderer::OnShutdown()
{
	SDL_DelEventWatch(watch, NULL);
	SDL_DestroyWindow(window);
	SDL_Quit();

	window = NULL;
	renderer = NULL;
}
