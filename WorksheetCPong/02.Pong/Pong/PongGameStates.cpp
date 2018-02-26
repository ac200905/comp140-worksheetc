#include "PongGameStates.h"
#include "Pong.h"
#include "../engine/Renderer.h"
#include "../engine/Input.h"

void GameState_Attract::Init()
{	
	Pong * game = Pong::Get();

	Timer = 0;
}

bool GameState_Attract::Update()
{		
	if (Input::Get()->GetKeyState(VK_SPACE) == KeyState_Pressed)
	{
		Pong::Get()->stateMachine.SetGameState(GameState_Serve::Label);
		Pong::Get()->OnNewGame();
	}

	Timer++;

	return true;
}

void GameState_Attract::Draw()
{
	Pong * game = Pong::Get();


	game->DrawCourt();
	game->DrawPlayers();
	game->DrawScore();

	
	Renderer::Get()->DrawRect(200-5, 200-5, 400+10, 350+10, RGBTOCOLOR(255,128,0));
	Renderer::Get()->DrawRect(200, 200,400,350, RGBTOCOLOR(0,0,255));

	Renderer::Get()->debugPrinter->SetScale(2, 2);
	Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Centre);

	Renderer::Get()->debugPrinter->Print(400, 210, RGBTOCOLOR(204, 0, 0), "PONG");

	Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Left);
	Renderer::Get()->debugPrinter->Print(210, 260, RGBTOCOLOR(255, 128, 0), "       Player 1 Player 2");
	Renderer::Get()->debugPrinter->Print(210, 310, RGBTOCOLOR(255, 128, 0), "   UP:    Q        P");
	Renderer::Get()->debugPrinter->Print(210, 360, RGBTOCOLOR(255, 128, 0), " DOWN:    A        L");
	Renderer::Get()->debugPrinter->Print(210, 410, RGBTOCOLOR(255, 128, 0), "SERVE: L. CTRL  R.CTRL");

	if (Timer % 20 > 10)
	{
		Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Centre);
		Renderer::Get()->debugPrinter->Print(400, 480, RGBTOCOLOR(255,0,0), "Press SPACE to play");
	}

	Renderer::Get()->debugPrinter->SetScale(1, 1);
	Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Left);
}

void GameState_Serve::Init()
{
        
}

bool GameState_Serve::Update()
{
	Pong * game = Pong::Get();
	
	game->GetPlayer(Player::Side_Left).Update();
	game->GetPlayer(Player::Side_Right).Update();
	
	if (game->GetPlayerToServe() == Player::Side_Left)
	{		
		if (Input::Get()->GetKeyState(VK_LCONTROL) != KeyState_NotPressed)
		{
			// serve			
			game->GetBall().Serve();
			Pong::Get()->stateMachine.SetGameState( GameState_Rally::Label);
		}
	}
	else
	{
		if (Input::Get()->GetKeyState(VK_RCONTROL) != KeyState_NotPressed)
		{
			// serve
			game->GetBall().Serve();
			Pong::Get()->stateMachine.SetGameState( GameState_Rally::Label);
		}
	}

	game->GetBall().SetPositionForServe(game->GetPlayer(game->GetPlayerToServe()));

	return true;
}

void GameState_Serve::Draw()
{
	Pong * game = Pong::Get();

	game->DrawCourt();
	game->DrawPlayers();
	game->DrawBall();
	game->DrawScore();
}

void GameState_Rally::Init()
{
}

bool GameState_Rally::Update()
{
	Pong * game = Pong::Get();

	
	if (((game->TheBall.IsColliding(game->ThePlayers[0]) == true) && (game->TheBall.IsGoingTo() == Player::Side_Left))
		|| ((game->TheBall.IsColliding(game->ThePlayers[1]) == true) && (game->TheBall.IsGoingTo() == Player::Side_Right))
		)
	{
		game->TheBall.PlayerReturns();
	}

	game->ThePlayers[0].Update();
	game->ThePlayers[1].Update();

	game->TheBall.Update();
	

	if (game->IsBallOut())
	{
		if(game->GetBall().posX > 400)
		{
			game->lastScore = Player::Side_Left;
		}
		else
		{
			game->lastScore = Player::Side_Right;
		}

		Pong::Get()->stateMachine.SetGameState( GameState_Miss::Label );
	}

	return true;
}

void GameState_Rally::Draw()
{
	Pong * game = Pong::Get();

	game->DrawCourt();
	game->DrawPlayers();
	game->DrawBall();
	game->DrawScore();
}


void GameState_Miss::Init()
{
	Timer = 0;
}

bool GameState_Miss::Update()
{
	Pong * game = Pong::Get();

	if (Timer == 20)
	{
		game->UpdateScore();
	}
	if (Timer > 40)
	{
		if (game->IsGameOver())
		{
			Pong::Get()->stateMachine.SetGameState( GameState_GameOver::Label );
		}
		else
		{
			Pong::Get()->stateMachine.SetGameState( GameState_Serve::Label);
		}
	}

	Timer++;
	return true;
}

void GameState_Miss::Draw()
{
	Pong * game = Pong::Get();

	game->DrawCourt();

	
	game->GetPlayer(game->GetWhichPlayerScored()).Draw();

	if (Timer % 10 < 5)
	{
		game->GetPlayer(game->GetWhichPlayerScored() == Player::Side_Right? Player::Side_Left:Player::Side_Right).Draw();
	}
	
	game->DrawScore();
	game->DrawBall();
}

void GameState_GameOver::Init()
{
	Timer = 0;
}

bool GameState_GameOver::Update()
{
	Pong * game = Pong::Get();

	if ( (Input::Get()->GetKeyState(VK_LCONTROL) != KeyState_NotPressed)
	   ||(Input::Get()->GetKeyState(VK_RCONTROL) != KeyState_NotPressed)	  
	  )
	 {
		 Pong::Get()->stateMachine.SetGameState( GameState_Attract::Label );
	 }

	 Timer++;
	 return true;
}

void GameState_GameOver::Draw()
{
	Pong * game = Pong::Get();

	game->DrawCourt();
	game->GetPlayer(game->GetWhichPlayerScored()).Draw();
	
	if (Timer % 10 < 5)
	{
		game->DrawScore();
	}
}