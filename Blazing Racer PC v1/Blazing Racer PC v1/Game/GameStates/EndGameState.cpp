#include "stdafx.h"
#include "Game/GameStates/EndGameState.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Util/Texture.h"
#include "Graphics/Camera.h"

using namespace GameState;
using namespace Graphics;


extern Camera *g_pCamera;


EndGameState::EndGameState(void)
{
	m_isPaused	 = false;
}

EndGameState::~EndGameState(void)
{
}

void EndGameState::Init()
{

}

void EndGameState::Update()
{
	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_A))
		GameHandler::GetInstance()->SetGameExit(true);


	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);
}

void EndGameState::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0L );
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderBeginScene();
	XUserInterface::GetInstance()->DrawText(0, XMFLOAT4(255, 0, 0, 100), 320, SCREEN_HEIGHT/2, L"CREDITS");
	XUserInterface::GetInstance()->DrawText(0, XMFLOAT4(255, 0, 0, 100), 320, SCREEN_HEIGHT/2 + 50, L"Press A to Exit");
	XUserInterface::GetInstance()->UIRenderEndScene();
#endif
}

void EndGameState::Destroy()
{

}
