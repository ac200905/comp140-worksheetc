#pragma once
#include "../engine/StateMachine.h"

class GameState_Attract : public StateMachine::State
{
	public:
		unsigned int Timer;

		void Init();
		bool Update();
		void Draw();

		static constexpr const char* Label = "Attract";
		const char* Name(){return Label;}
};

class GameState_Serve :  public StateMachine::State
{
	public:		
		virtual void Init();
		virtual bool Update();
		virtual void Draw();

		static constexpr const char* Label = "Serve";
		const char* Name() { return Label; }
};

class GameState_Rally :  public StateMachine::State
{
	public:		
		virtual void Init();
		virtual bool Update();
		virtual void Draw();

		static constexpr const char* Label = "Rally";
		const char* Name() { return Label; }
};

class GameState_Miss :  public StateMachine::State
{
	private:
        unsigned int Timer;

	public:		
		virtual void Init();
		virtual bool Update();
		virtual void Draw();

		static constexpr const char* Label = "Miss";
		const char* Name() { return Label; }
 
};

class GameState_GameOver :  public StateMachine::State
{
    private:
        unsigned int Timer;

	public:		
		virtual void Init();
		virtual bool Update();
		virtual void Draw();

		static constexpr const char* Label = "Game Over";
		const char* Name() { return Label; }
};