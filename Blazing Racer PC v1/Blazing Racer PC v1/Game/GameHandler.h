#pragma once

#ifndef __GAMEHANDLER__
#define __GAMEHANDLER__

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<map>
#include "Game/GameStates/IGameState.h"

using namespace std;
using namespace GameState;

class GameHandler
{
	static GameHandler					*ms_pGameHandler;

	map<EGameState,IGameState*>			 m_StateMap;
	vector<IGameState*>					 m_StateStack;
	BOOL								 m_IsGameExit;
	EGameState							 m_CurrentGameState;
	EGameMode							 m_GameMode;

										 GameHandler();
	void								 PushState(IGameState *_gameState);
	IGameState*							 PopState();

public:
	~GameHandler(void);
	static GameHandler*					 GetInstance();
	void								 Init();
	void								 Update();
	void								 Render();
	void								 Destroy();

	void								 SetState(EGameState _eGameState,EWhatToDoWithPreviousState _what);
	EGameState							 GetCurrentState();

	EGameMode							 GetCurrentGameMode()						{ return m_GameMode;  }
	void								 SetGameMode(EGameMode _mode)				{ m_GameMode = _mode; }

	void								 SetGameExit(bool value);
	bool								 GetGameExit();
};

#endif
