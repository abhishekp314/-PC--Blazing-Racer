#pragma once

#ifndef __ENDGAMESTATE__
#define __ENDGAMESTATE__

#include "Game/GameStates/IGameState.h"

namespace GameState
{

class EndGameState:public IGameState
	{
	public:
		EndGameState(void);
		~EndGameState(void);
		void Init();
		void Update();
		void Render();
		void Destroy();
	};

}
#endif