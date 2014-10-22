#include "stdafx.h"
#include "Game/GameStates/NewGameState.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Util/Texture.h"
#include "Graphics/Camera.h"

using namespace GameState;
using namespace Graphics;
using namespace Util;

extern Camera*		g_pCamera;

NewGameState::NewGameState(void)
{
	m_isPaused	 = false;
}


NewGameState::~NewGameState(void)
{
}

void NewGameState::Init()
{
#ifdef XBOX
	Texture *pTex = ResourceManager::GetInstance()->Load<Texture>("Game:\\Content\\Textures\\newgame.jpg");
#else
	Texture *pTex = ResourceManager::GetInstance()->Load<Texture>("Content\\Textures\\newgame.jpg");
#endif
	m_pSprite = new XSprite();
	m_pSprite->InitSprite(-SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 720, 1280, pTex->GetTexture(), 1, false);
}

void NewGameState::Update()
{
	if (InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_A) || GetAsyncKeyState(VK_UP))
	{
		GameHandler::GetInstance()->SetState(GAMESTATE_RUNNING,STATE_DESTROY);
		GameHandler::GetInstance()->SetGameMode(GAMEMODE_SINGLEPLAYER);
	}

	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_B))
	{
		GameHandler::GetInstance()->SetState(GAMESTATE_CONNECTION,STATE_DESTROY);
		GameHandler::GetInstance()->SetGameMode(GAMEMODE_MULTIPLAYER);
	}

	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_BACK))
		GameHandler::GetInstance()->SetState(GAMESTATE_END,STATE_DESTROY);


	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);
	m_pSprite->Update();

#ifdef XBOX
	XUserInterface::GetInstance()->Update();
#endif
}

void NewGameState::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 
		D3DCOLOR_XRGB(255,255,0), 1.0f, 0L );

	m_pSprite->Render(XGraphics::GetInstance()->GetDevice(), ALP_CUT, g_pCamera->GetViewMat(), g_pCamera->GetProjMat(), XMFLOAT4(255, 255, 255, 255));
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderBeginScene();
	XUserInterface::GetInstance()->DrawText(1, XMFLOAT4(100, 100, 200, 255), 0, 0, L"New Game");
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 50, L"Press A for Single Player", 1);
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 100, L"Press B for Multi Player", 1);
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 150, L"Press BACK to Exit Game", 1);

	XUserInterface::GetInstance()->DrawText(2, XMFLOAT4(0, 150, 0, 255), 0, SCREEN_HEIGHT - 200, L"Use LEFT THUMB STICK to control the steer car Left and Right");
	XUserInterface::GetInstance()->DrawText(2, XMFLOAT4(0, 150, 0, 255), 0, SCREEN_HEIGHT - 100, L"Use RT to Accelerate and LT to Accelerate Reverse");
	XUserInterface::GetInstance()->DrawText(2, XMFLOAT4(0, 150, 0, 255), 0, SCREEN_HEIGHT - 150, L"Use LB to apply NOS when Activated");
	XUserInterface::GetInstance()->DrawText(2, XMFLOAT4(0, 150, 0, 255), 0, SCREEN_HEIGHT -  50, L"Use START BUTTON to Pause the Game");
	
	XUserInterface::GetInstance()->UIRenderEndScene();
#endif
}

void NewGameState::Destroy()
{

}