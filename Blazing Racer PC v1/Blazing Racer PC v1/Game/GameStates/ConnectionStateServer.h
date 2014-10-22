#pragma once

#ifndef __CONNECTIONSERVERSTATE__
#define __CONNECTIONSERVERSTATE__

#include "Game/GameStates/IGameState.h"
#include "Network/NetworkManager.h"

namespace GameState
{
	class ConnectionStateServer:public IGameState
	{
		Server* m_pServer;
	public:
		ConnectionStateServer(void);
		~ConnectionStateServer(void);
		void Init();
		void Update();
		void Render();
		void Destroy();
	};
}
#endif