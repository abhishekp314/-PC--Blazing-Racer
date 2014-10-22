#include "stdafx.h"
#include "NetworkManager.h"

#ifdef XBOX
#include "DarkNet/Classes/Server.h"
#include "DarkNet/Classes/Client.h"
#include "DarkNet/Classes/DarkNetFuncs.h"
#else
#include "Network/DarkNet/Server.h"
#include "Network/DarkNet/Client.h"
#include "Network/DarkNet/DarkNetFuncs.h"
#endif

#include "Game/GameStates/ConnectionStateServer.h"
#include "Game/GameStates/ConnectionStateClient.h"

NetworkManager* NetworkManager::m_NM=nullptr;
Server* NetworkManager::m_pServer=nullptr;
Client* NetworkManager::m_pClient=nullptr;
vector<std::string> NetworkManager::m_ServerIpList;
int NetworkManager::m_LocalPlayerIndex;
int NetworkManager::m_NumberOfPlayers;
bool NetworkManager::m_IsStarted=false;

Connection g_pClientCon;

extern D3DXCOLOR g_ConServerStateColor;
extern D3DXCOLOR g_ConClientStateColor;

NetworkManager::NetworkManager(void)
{
	m_NumberOfPlayers=0;
	m_LocalPlayerIndex=-999;
}

NetworkManager::~NetworkManager(void)
{

}

int getNextSpace(string _str, int _startIndex);

bool NetworkManager::Init(EConnectionType _type)
{
	if(_type==CONNECTIONTYPE_SERVER)
	{
		m_pServer=new Server();
		m_pServer->CreateServer(1050, 1);
		m_pServer->StartListening(CONNECTION_REQUEST,true, onConnectionFound_Server, OnDataRecieved_Server);
		return true;
	}
	else if(_type==CONNECTIONTYPE_CLIENT)
	{
		m_pClient=new Client();
		m_pClient->Start(1050, true, onConnectionFound_Client, OnDataRecieved_Client);
		int result = m_pClient->Broadcast("IP_REQUEST");
		return true;
	}
	else if(_type==CONNECTIONTYPE_NONE)
	{
		return false;
	}
	return false;
}

void NetworkManager::Update()
{

}

NetworkManager* NetworkManager::getInstance()
{
	return m_NM;
}

bool NetworkManager::isHost()
{
	if(m_pServer)
	{
		return true;
	}
	
	return false;
}

void NetworkManager::onConnectionFound_Client(void * _params)
{
	g_ConClientStateColor=D3DCOLOR_XRGB(0,0,0);
}

void NetworkManager::onConnectionFound_Server(void * _params)
{
	g_ConServerStateColor=D3DCOLOR_XRGB(255,255,255);

	g_pClientCon=*(Connection*)_params;
}

void NetworkManager::OnDataRecieved_Client(char* _data, void* _tag)
{
	char tempBuff[NETWORK_BUFFER_LENGTH];
	if(strstr(_data,"IP:"))
	{
		SocketAddress* addr=(SocketAddress*)(_tag);
		char buff[NETWORK_BUFFER_LENGTH];
		strcpy(buff,DarkNet::GetIp(addr));
		m_ServerIpList.push_back(buff);
	}
	else if(strstr(_data,"START"))
	{
		string word;

		int spacePos; 
		int spacePos2;

		string data=_data;
		spacePos = data.find_first_of(" ");
		spacePos2 = getNextSpace(data, spacePos+1);

		word = data.substr(spacePos+1, spacePos2-spacePos-1);

		m_NumberOfPlayers=atoi(word.c_str());

		spacePos=spacePos2;

		spacePos2 = getNextSpace(data, spacePos+1);
		word = data.substr(spacePos+1, spacePos2-spacePos-1);

		m_LocalPlayerIndex=atoi(word.c_str());

		m_IsStarted=true;
	}
	else
	{
		OutputDebugString(_data);
	}

}

void NetworkManager::OnDataRecieved_Server(char* _data, void* _tag)
{
	char buff[NETWORK_BUFFER_LENGTH];

	if(!strcmp(_data,"IP_REQUEST"))
	{
		strcpy(buff,"IP:");
		strcat(buff,"\0");
		m_pServer->Broadcast(buff);
	}
}

bool NetworkManager::ServersAvailable()
{
	if(m_ServerIpList.size()>0)
	{
		return true;
	}
	return false;
}

void NetworkManager::Connect(int _index)
{
	if(_index-1<m_ServerIpList.size())
	{
		m_pClient->Connect((char*)m_ServerIpList[_index-1].c_str(), CONNECTION_REQUEST);
	}
}

int getNextSpace(string _str, int _startIndex)
{
	int i;
	for(i=_startIndex; i<_str.length(); i++)
	{
		if(_str[i]==' ')
		{
			break;
		}
	}
	return i;
}