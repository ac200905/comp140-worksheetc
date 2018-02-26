#pragma once
#include <SDL.h>
#include "typedef.h"
#include "Singleton.h"
#include "DebugPrinter.h"


int RGBATOCOLOR(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
int RGBTOCOLOR(unsigned char r, unsigned char g, unsigned char b);
void COLORTORGBA(int col, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a);

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))


class Renderer : public Singleton<Renderer>
{
public:
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	bool OnStartUp();

	void DrawRect(float x, float y, float w, float h,u32 col);

	void OnShutdown();
	
	DebugPrinter* debugPrinter;
private:
	
};
