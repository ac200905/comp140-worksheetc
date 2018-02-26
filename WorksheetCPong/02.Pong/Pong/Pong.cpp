#include "Pong.h"
#include <stdio.h>
#include "../engine/Renderer.h"

#include "PongGameStates.h"
#include <iostream>

bool Pong::OnOneTimeInit()
{
	stateMachine.AddState(GameState_Attract::Label, new GameState_Attract());

	stateMachine.AddState(GameState_Serve::Label, new GameState_Serve());
	stateMachine.AddState(GameState_Rally::Label, new GameState_Rally());
	stateMachine.AddState(GameState_Miss::Label, new GameState_Miss());
	stateMachine.AddState(GameState_GameOver::Label, new GameState_GameOver());

	stateMachine.SetGameState(GameState_Attract::Label);

	//create the serial interface
	serialInterface = new SerialInterface;

	return true;
}

void Pong::OnNewGame()
{

	ThePlayers[0].Init();
	ThePlayers[0].SetSide(Player::Side_Left);

	ThePlayers[1].Init();
	ThePlayers[1].SetSide(Player::Side_Right);

	TheBall.Init();

	Score[0] = 0;
	Score[1] = 0;

	lastScore = Player::Side_Undefined;
	
}

bool Pong::Init()
{
	ThePlayers[0].Init();
	ThePlayers[0].SetSide(Player::Side_Left);

	ThePlayers[1].Init();
	ThePlayers[1].SetSide(Player::Side_Right);

	TheBall.Init();

	Score[0] = 0;
	Score[1] = 0;

	return true;
}

bool Pong::Update()
{
	

	//Get potentiometer readings
	serialInterface->getPositions();

	//Assign the y position of each player to the potentiometer values
	ThePlayers[0].posY = serialInterface->getPot1();
	ThePlayers[1].posY = serialInterface->getPot2();
	
	//Set the player 1 boundaries
	if (ThePlayers[0].posY < 100)
	{
		ThePlayers[0].posY = 100;
	}
	if (ThePlayers[0].posY > 540)
	{
		ThePlayers[0].posY = 540;
	}

	//Set the player 2 boundaries
	if (ThePlayers[1].posY < 100)
	{
		ThePlayers[1].posY = 100;
	}
	if (ThePlayers[1].posY > 540)
	{
		ThePlayers[1].posY = 540;
	}

	return stateMachine.Update();
	return true;
}

bool Pong::Draw()
{
	SDL_SetRenderDrawColor(Renderer::Get()->renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer::Get()->renderer);

	stateMachine.Draw();
#if false
		SDL_Rect rect;

		rect.x = 0;
		rect.y = 0;
		rect.w = 800;
		rect.h = 600;
		
		SDL_SetRenderDrawColor(Renderer::Get()->renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(Renderer::Get()->renderer, &rect);

		DrawCourt();

		ThePlayers[0].Draw();
		ThePlayers[1].Draw();

		TheBall.Draw();

		char str[255];
		sprintf(str,"%d - %d",Score[0],Score[1]);

		Renderer::Get()->debugPrinter->SetScale(8, 8);
		Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justifiy_Centre);
		Renderer::Get()->debugPrinter->Print(400,20,RGBTOCOLOR(255,255,255),str);
		Renderer::Get()->debugPrinter->SetScale(1, 1);
		Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justifiy_Left);
		
#endif	
	return true;
}

bool Pong::Shutdown()
{
	return true;
}

Player& Pong::GetPlayer(Player::Side side)
{
	if (side == Player::Side_Left) return ThePlayers[0];
	if (side == Player::Side_Right) return ThePlayers[1];

	throw "undefined";
}

Ball& Pong::GetBall()
{
	return TheBall;
}

void Pong::DrawCourt()
{
	Renderer::Get()->DrawRect(0, 0, 800, 600, RGBTOCOLOR(0, 128, 255));

	Renderer::Get()->DrawRect(0, 100, 800, 10, RGBTOCOLOR(255, 128, 0));
	Renderer::Get()->DrawRect(0, 590, 800, 10, RGBTOCOLOR(255, 128, 0));
	Renderer::Get()->DrawRect(395, 100, 10, 600, RGBTOCOLOR(255, 128, 0));
}

void Pong::DrawScore()
{
	char str[255];
	sprintf(str, "%d - %d", Score[0], Score[1]);

	Renderer::Get()->debugPrinter->SetScale(8, 8);
	Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Centre);
	Renderer::Get()->debugPrinter->Print(400, 20, RGBTOCOLOR(255, 128, 0), str);
	Renderer::Get()->debugPrinter->SetScale(1, 1);
	Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Left);

}

void Pong::DrawBall()
{
	TheBall.Draw();
}


void Pong::UpdateScore()
{
	if (TheBall.OutOfBoundsSide() == Player::Side_Left)
	{
		//flash the right LED if player 1 scores
		serialInterface->LEDGoal("R");
		Score[1]++;
	}

	if (TheBall.OutOfBoundsSide() == Player::Side_Right)
	{
		//flash the left LED if player 2 scores
		serialInterface->LEDGoal("L");
		Score[0]++;
	}
}

bool Pong::IsBallOut()
{
	return TheBall.IsOutOfBounds();
}

bool Pong::IsGameOver()
{
	return ((Score[0] > 3) || (Score[1] > 3));
}

Player::Side  Pong::GetWhichPlayerScored()
{
	return lastScore;
}

Player::Side  Pong::GetPlayerToServe()
{
	if ((Score[0] == 0) && (Score[1] == 0))	return Player::Side_Left;
	return GetWhichPlayerScored();
}

void Pong::DrawPlayers()
{
	ThePlayers[0].Draw();
	ThePlayers[1].Draw();
}



#if false
void Pong::Print(int x, int y, int color, const char* text)
{
	Renderer::Get()->debugPrinter->Print(x, y, color, text);
}

#endif

void Pong::clean()
{
	std::cout << "Cleaning SDL \n";
	SDL_Quit();
}

