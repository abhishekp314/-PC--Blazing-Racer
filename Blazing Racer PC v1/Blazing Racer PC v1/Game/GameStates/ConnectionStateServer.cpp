#include "stdafx.h"
#include "Game/GameStates/ConnectionStateServer.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Graphics/Camera.h"

using namespace GameState;
using namespace Graphics;

D3DXCOLOR g_ConServerStateColor;

extern Connection g_pClientCon;


extern Camera *g_pCamera;


ConnectionStateServer::ConnectionStateServer(void)
{
	m_isPaused = false;
	m_pServer=nullptr;
	g_ConServerStateColor=D3DCOLOR_XRGB(0,255,255);
}


ConnectionStateServer::~ConnectionStateServer(void)
{
}

void ConnectionStateServer::Init()
{
	NetworkManager::getInstance()->Init(CONNECTIONTYPE_SERVER);

	m_pServer=NetworkManager::getInstance()->getServer();
}

void ConnectionStateServer::Update()
{
	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_START))
	{
		//make START packet and go to running
		std::vector<Connection>	Connections = m_pServer->GetConnections();

		char buff[NETWORK_BUFFER_LENGTH];

		for(int i=0;i<Connections.size();i++)
		{
			sprintf(buff,"START %d %d",Connections.size()+1,i+1);
			m_pServer->Send(Connections[i].address,buff);
		}

		NetworkManager::getInstance()->setLocalPlayerIndex(0);
		NetworkManager::getInstance()->setNumberOfPlayers(Connections.size()+1);

		GameHandler::GetInstance()->SetState(GAMESTATE_RUNNING, STATE_DESTROY);
	}


	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);
}	

void ConnectionStateServer::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 
		g_ConServerStateColor, 1.0f, 0L );

	wchar_t s[256];
	swprintf(s, L" Number of Players %d", NetworkManager::getInstance()->GetNumberOfPlayers());
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderBeginScene();
	XUserInterface::GetInstance()->DrawText(1, XMFLOAT4(100, 100, 200, 255), 0, 0, L"Connected Clients");
	XUserInterface::GetInstance()->DrawText(0, XMFLOAT4(100, 100, 200, 255), 0, 50, s);
	XUserInterface::GetInstance()->UIRenderEndScene();
#endif
}

void ConnectionStateServer::Destroy()
{

}