#pragma once
#include <SDL.h>

class Object
{
public:
	void virtual Init()=0;
	void virtual Update() = 0;
	void virtual Draw();

	bool virtual IsColliding(const Object& o);

	float posX,posY;
	float w,h;
};
