#pragma once
#include <map>
#include <SDL.h>

class StateMachine
{
public:

	class State
	{
	public:
		virtual void Init() = 0;
		virtual bool Update() { return true; }
		virtual void Draw() = 0;
		virtual void Exit() {};

		virtual const char* Name()
		{
			return "No label defined";
		}
	};

	StateMachine();

	void Init();
	void SetGameState(const char* NewState);
	bool Update();
	void Draw();
	void Exit();

	std::map<const char*, State*> stateDictionary;

	void AddState(const char* name, State* state);

private:

	void Reset();

	const char* TheGameState;
	const char* TheNextGameState;

};