#include "StateMachine.h"
#include <stdlib.h>



StateMachine::StateMachine()
{
	Reset();
}

void StateMachine::AddState(const char * name, State * state)
{
	if (stateDictionary.find(name) == stateDictionary.end())
	{
		stateDictionary.insert(std::pair<const char*, State*>(name, state));
	}
}

void StateMachine::Reset()
{
	TheGameState = NULL;
	TheNextGameState = NULL;
}

void StateMachine::Init()
{
	if (TheGameState != NULL)
	{
		stateDictionary[TheGameState]->Init();
	}
	else
	{
		if (TheNextGameState != NULL)
		{
			if (TheGameState != NULL)
			{
				stateDictionary[TheGameState]->Exit();

			}

			TheGameState = TheNextGameState;
			TheNextGameState = NULL;
		}

		if (TheGameState)
		{
			stateDictionary[TheGameState]->Init();
		}
	}
}

void StateMachine::SetGameState(const char * NewState)
{
	TheNextGameState = NewState;
}


bool StateMachine::Update()
{
	if (TheNextGameState != NULL)
	{
		if (TheGameState != NULL)
		{
			stateDictionary[TheGameState]->Exit();
		}

		TheGameState = TheNextGameState;
		TheNextGameState = NULL;

		stateDictionary[TheGameState]->Init();
	}


	if (TheGameState == NULL)
	{
		return true;
	}
	return stateDictionary[TheGameState]->Update();

}

void StateMachine::Draw()
{

	if (TheGameState != NULL)
	{
		stateDictionary[TheGameState]->Draw();
	}
}

void StateMachine::Exit()
{
	if (TheGameState != NULL)
	{
		stateDictionary[TheGameState]->Exit();

		TheGameState = NULL;
	}

	if (TheNextGameState != NULL)
	{
		TheNextGameState = NULL;
	}
}