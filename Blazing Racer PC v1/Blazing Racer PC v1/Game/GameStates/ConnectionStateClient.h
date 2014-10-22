#pragma once

#ifndef __CONNECTIONCLIENTSTATE__
#define __CONNECTIONCLIENTSTATE__

#include "Game/GameStates/IGameState.h"
#include "Network/NetworkManager.h"
#include "DarkNet/Classes/Client.h"

namespace GameState
{
	class ConnectionStateClient:public IGameState
	{
		Client* m_pClient;
	public:
		ConnectionStateClient(void);
		~ConnectionStateClient(void);
		void Init();
		void Update();
		void Render();
		void Destroy();
	};
}
#endif

