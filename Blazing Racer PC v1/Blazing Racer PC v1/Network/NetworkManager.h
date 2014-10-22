#pragma once

#ifndef __NET_MANAGER__
#define __NET_MANAGER__

#ifdef XBOX
#include "DarkNet/Classes/Server.h"
#include "DarkNet/Classes/Client.h"
#include "DarkNet/Classes/DarkNetFuncs.h"
#else
#include "Network/DarkNet/Server.h"
#include "Network/DarkNet/Client.h"
#include "Network/DarkNet/DarkNetFuncs.h"
#endif

#include <vector>

#include "Game/GameStates/IGameState.h"
#include "Game/GameHandler.h"

class NetworkManager
{
	static NetworkManager* m_NM;
	static Server* m_pServer;
	static Client* m_pClient;
	static vector<std::string> m_ServerIpList;
	std::vector<string>  m_InputList;
	static int m_NumberOfPlayers;
	static int m_LocalPlayerIndex;
	static bool m_IsStarted;

	NetworkManager(void);
public:
	~NetworkManager(void);
	static NetworkManager* getInstance();
	bool Init(EConnectionType _type);
	void Update();
	bool isHost();
	bool ServersAvailable();

	void Connect(int index);

	//declaring callbacks
	static void onConnectionFound_Client(void * _params);
	static void onConnectionFound_Server(void * _params);
	static void OnDataRecieved_Client(char* _data, void* _tag);
	static void OnDataRecieved_Server(char* _data, void* _tag);

	Server* getServer()				{ return m_pServer; }
	Client* getClient()				{ return m_pClient; }
	int		GetNumberOfPlayers()	{ return m_NumberOfPlayers;}
	int		GetLocalPlayerIndex()	{ return m_LocalPlayerIndex;}
	bool	isStarted()				{ return m_IsStarted; }
	void	setNumberOfPlayers(int _NOP)	{ m_NumberOfPlayers=_NOP; }
	void	setLocalPlayerIndex(int _LPI)	{ m_LocalPlayerIndex=_LPI; }
	std::vector<string>	getServerIPList()		{ return m_ServerIpList; }
};

#endif