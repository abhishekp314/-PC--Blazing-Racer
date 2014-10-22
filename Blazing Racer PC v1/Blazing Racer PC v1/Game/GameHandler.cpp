#include "stdafx.h"
#include "Game/GameHandler.h"
#include "Game/GameStates/IntroState.h"
#include "Game/GameStates/MainMenuState.h"
#include "Game/GameStates/ConnectionState.h"
#include "Game/GameStates/RunningState.h"
#include "Game/GameStates/PauseState.h"
#include "Game/GameStates/NewGameState.h"
#include "Game/GameStates/EndGameState.h"
#include "Game/GameStates/ConnectionStateServer.h"
#include "Game/GameStates/ConnectionStateClient.h"
#include "Game/GameStates/GameOver.h"


GameHandler* GameHandler::ms_pGameHandler=nullptr;

GameHandler::GameHandler()
{

}

GameHandler::~GameHandler(void)
{
}

GameHandler* GameHandler::GetInstance()
{
	if(ms_pGameHandler==nullptr)
		ms_pGameHandler=new GameHandler();

	return ms_pGameHandler;
}


void GameHandler::Init()
{
	m_StateMap[GAMESTATE_INTRO] = new IntroState();
	m_StateMap[GAMESTATE_MAINMENU] = new MainMenuState();
	m_StateMap[GAMESTATE_NEWGAME] = new NewGameState();
	m_StateMap[GAMESTATE_CONNECTION] = new ConnectionState();
	m_StateMap[GAMESTATE_CONNECTIONSTATE_SERVER] = new ConnectionStateServer();
	m_StateMap[GAMESTATE_CONNECTIONSTATE_CLIENT] = new ConnectionStateClient();
	m_StateMap[GAMESTATE_RUNNING] = new RunningState();
	m_StateMap[GAMESTATE_PAUSE] = new PauseState();
	m_StateMap[GAMESTATE_GAMEOVER] = new GameOver();
	m_StateMap[GAMESTATE_END] = new EndGameState();

	m_IsGameExit=false;
	m_GameMode = GAMEMODE_SINGLEPLAYER;

	SetState(GAMESTATE_INTRO, STATE_NONE);
}

void GameHandler::Update()
{
	m_StateStack.back()->Update();
}

void GameHandler::Render()
{
	m_StateStack.back()->Render();
}

void GameHandler::Destroy()
{

}

void GameHandler::SetState(EGameState _egs,EWhatToDoWithPreviousState _what)
{
	IGameState *tempState=nullptr;
	switch(_what)
	{
	case STATE_STORE:
		tempState=m_StateMap[_egs];
		PushState(tempState);
		break;
	case STATE_DESTROY: 
		PopState();
		tempState=m_StateMap[_egs];
		PushState(tempState);
		break;
	case STATE_NONE:
		tempState=m_StateMap[_egs];
		PushState(tempState);
		break;
	default: break;
	}

	if(!m_StateStack.back()->GetPauseState())
	{
		m_StateStack.back()->Init();
	}
	m_CurrentGameState=_egs;
}

void GameHandler::PushState(IGameState *_pGs)
{
	m_StateStack.push_back(_pGs); 
}

IGameState* GameHandler::PopState()
{
	IGameState* temp=m_StateStack.back();
	m_StateStack.pop_back();
	return temp;
}

EGameState GameHandler::GetCurrentState()
{
	return m_CurrentGameState;
}

void GameHandler::SetGameExit(bool value)
{
	m_IsGameExit=value;
}

bool GameHandler::GetGameExit()
{
	return m_IsGameExit;
} 