#include "stdafx.h"
#include "GameOver.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Graphics/XGraphics.h"
#include "Graphics/Camera.h"


using namespace GameState;
using namespace Graphics;

extern Camera *g_pCamera;

GameOver::GameOver(void)
{
}


GameOver::~GameOver(void)
{
}


void GameOver::Init()
{

}

void GameOver::Update()
{
	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_START))
		GameHandler::GetInstance()->SetState(GAMESTATE_MAINMENU,STATE_DESTROY);

	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_BACK))
		GameHandler::GetInstance()->SetState(GAMESTATE_END,STATE_DESTROY);
#ifdef XBOX
	XUserInterface::GetInstance()->Update();
#endif
	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);
}

void GameOver::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 
		D3DCOLOR_XRGB(255,255,0), 1.0f, 0L );
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderBeginScene();
	XUserInterface::GetInstance()->DrawText(1, XMFLOAT4(100, 100, 200, 255), SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2, L"GAME OVER");
	XUserInterface::GetInstance()->DrawAnimatedText(1, XMFLOAT4(200, 100, 100, 255), SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 100, L"Winner is Player ", 1);

	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 150, L"Press START to Go Back to Main Menu", 1);

	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 200, L"Press BACK to Exit Game", 1);
	XUserInterface::GetInstance()->UIRenderEndScene();
#endif
}

void GameOver::Destroy()
{

}