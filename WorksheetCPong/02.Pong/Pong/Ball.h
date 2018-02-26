#pragma once
#include "Object.h"
#include "Player.h"

class Ball : public Object
{
public:
	void Init();
	void Update();
	
	void PlayerReturns();
	bool IsOutOfBounds();
	Player::Side OutOfBoundsSide();
	Player::Side IsGoingTo();

	void ServeTo(Player::Side serveTo);
	void Serve();
	void SetPositionForServe(Object& o);
private:
	float dx,dy;
};