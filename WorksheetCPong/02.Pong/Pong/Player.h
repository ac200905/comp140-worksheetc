#pragma once
#include "Object.h"
#include "SerialInterface.h"


class Player : public Object
{
public:
	void virtual Init();
	void virtual Update();
	
	enum Side{Side_Undefined,Side_Left,Side_Right};
	void SetSide(Side eSide);

private:
	Side mySide;
	int speed;
	
};
