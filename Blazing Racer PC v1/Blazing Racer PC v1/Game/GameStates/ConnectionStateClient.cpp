#include "stdafx.h"
#include "Game/GameStates/ConnectionStateClient.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Graphics/Camera.h"

using namespace GameState;
using namespace Graphics;

D3DXCOLOR g_ConClientStateColor;


extern Camera *g_pCamera;


ConnectionStateClient::ConnectionStateClient(void)
{
	m_isPaused = false;
	m_pClient=nullptr;
	g_ConClientStateColor=D3DCOLOR_XRGB(0,255,0);
}


ConnectionStateClient::~ConnectionStateClient(void)
{
}

void ConnectionStateClient::Init()
{
	NetworkManager::getInstance()->Init(CONNECTIONTYPE_CLIENT);
	m_pClient=NetworkManager::getInstance()->getClient();
}

void ConnectionStateClient::Update()
{

	if(NetworkManager::getInstance()->ServersAvailable())
	{
		if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_DPAD_UP))
		{
			NetworkManager::getInstance()->Connect(1);
		}

		if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_DPAD_RIGHT))
		{
			NetworkManager::getInstance()->Connect(2);
		}

		if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			NetworkManager::getInstance()->Connect(3);
		}

		if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			NetworkManager::getInstance()->Connect(4);
		}
	}

	if(NetworkManager::getInstance()->isStarted())
	{
		GameHandler::GetInstance()->SetState(GAMESTATE_RUNNING,STATE_DESTROY);
	}


	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);
}

void ConnectionStateClient::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 
		g_ConClientStateColor, 1.0f, 0L );
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderBeginScene();
	XUserInterface::GetInstance()->DrawText(1, XMFLOAT4(100, 100, 200, 255), 0, 0, L"Available Server List");
#endif
	vector<string> list = NetworkManager::getInstance()->getServerIPList();
	for(int i=0; i < list.size(); i++)
	{
		char *t = (char *)list[i].c_str();
		wchar_t wt[256];
		swprintf(wt, L"IP : %S", t);
#ifdef XBOX
		XUserInterface::GetInstance()->DrawText(0, XMFLOAT4(100, 100, 200, 255), 0, (i+1) * 20, wt);
#endif
	}
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderEndScene();
#endif
}

void ConnectionStateClient::Destroy()
{

}