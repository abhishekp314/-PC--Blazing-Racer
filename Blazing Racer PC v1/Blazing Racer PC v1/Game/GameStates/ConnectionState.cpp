#include "stdafx.h"
#include "Game/GameStates/ConnectionState.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Graphics/Camera.h"

using namespace GameState;
using namespace Graphics;

extern Camera *g_pCamera;

ConnectionState::ConnectionState(void)
{
	m_isPaused	 = false;
	m_isStateDecided = false;
}


ConnectionState::~ConnectionState(void)
{
}

void ConnectionState::Init()
{
}

void ConnectionState::Update()
{
	if(!m_isStateDecided)
	{
		if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_X))//for host
		{
			m_isStateDecided=true;

			GameHandler::GetInstance()->SetState(GAMESTATE_CONNECTIONSTATE_SERVER, STATE_DESTROY);
		}

		if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_Y))
		{
			m_isStateDecided=true;

			GameHandler::GetInstance()->SetState(GAMESTATE_CONNECTIONSTATE_CLIENT, STATE_DESTROY);
		}

		if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_BACK))
			GameHandler::GetInstance()->SetState(GAMESTATE_END, STATE_DESTROY);
#ifdef XBOX
		XUserInterface::GetInstance()->Update();
#endif
	}


	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);
	
}

void ConnectionState::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 
		D3DCOLOR_XRGB(0,255,255), 1.0f, 0L );
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderBeginScene();
	XUserInterface::GetInstance()->DrawText(0, XMFLOAT4(255, 0, 0, 100), 0, 0, L"Multiplayer Game");
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 50, L"Press X to Host Game", 1);
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 100, L"Press Y to Join Game", 1);
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 150, L"Press BACK to Exit Game", 1);
	XUserInterface::GetInstance()->UIRenderEndScene();
#endif
}

void ConnectionState::Destroy()
{

}