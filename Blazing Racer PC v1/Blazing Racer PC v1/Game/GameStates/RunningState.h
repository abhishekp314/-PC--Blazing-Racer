#pragma once

#ifndef __RUNNINGSTATE__
#define __RUNNINGSTATE__

#include "Game/GameStates/IGameState.h"
#include "Game/GameActors/SimpleActor.h"
#include "Game/GameActors/PhysicsActor.h"
#include "Game/GameActors/Car.h"
#include "Util/Util.h"

namespace GameState
{

	class RunningState:public IGameState
	{
		PhysicsActor			*m_pPlayer1, *m_pPlayer2;
		AnimatedActor			*m_pAnimatedRoad;
		int						 m_LocalPlayerIndex;
		int						 m_NumberOfPlayers;
		vector<Car*>			 m_PlayerList;
		short					 m_pitchLevel;
		EGameMode				 m_GameMode;

	public:
		RunningState(void);
		~RunningState(void);
		void					Init();
		void					Update();
		void					Render();
		void					Destroy();
	};

}

#endif