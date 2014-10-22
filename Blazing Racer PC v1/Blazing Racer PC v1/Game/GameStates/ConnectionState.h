#pragma once

#ifndef __CONNECTIONSTATE__
#define __CONNECTIONSTATE__

#include "Game/GameStates/IGameState.h"

namespace GameState
{
	class ConnectionState:public IGameState
	{
		bool m_isStateDecided;
	public:
		ConnectionState(void);
		~ConnectionState(void);
		void Init();
		void Update();
		void Render();
		void Destroy();
	};
}
#endif

