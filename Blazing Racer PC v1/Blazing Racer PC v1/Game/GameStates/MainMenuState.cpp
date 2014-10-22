#include "stdafx.h"
#include "Game/GameStates/MainMenuState.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Util/Texture.h"
#include "Graphics/Camera.h"

using namespace Util;
using namespace GameState;
using namespace Graphics;

extern Camera*		g_pCamera;

MainMenuState::MainMenuState(void)
{
	m_isPaused	 = false;
}

MainMenuState::~MainMenuState(void)
{
}

void MainMenuState::Init()
{
#ifdef XBOX
	Texture *pTex = ResourceManager::GetInstance()->Load<Texture>("Game:\\Content\\Textures\\mainmenu.jpg");
#else
	Texture *pTex = ResourceManager::GetInstance()->Load<Texture>("Content\\Textures\\mainmenu.jpg");
#endif
	m_pSprite = new XSprite();
	m_pSprite->InitSprite(-SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 720, 1280, pTex->GetTexture(), 1, false);
}

void MainMenuState::Update()
{
	if (InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_START) || GetAsyncKeyState(VK_DOWN))
		GameHandler::GetInstance()->SetState(GAMESTATE_NEWGAME, STATE_DESTROY);

	if (InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_BACK) || GetAsyncKeyState(VK_ESCAPE))
		GameHandler::GetInstance()->SetState(GAMESTATE_END, STATE_DESTROY);

	m_pSprite->Update();
#ifdef XBOX
	XUserInterface::GetInstance()->Update();
#endif
	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);
}

void MainMenuState::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 
		D3DCOLOR_XRGB(255,0,0), 1.0f, 0L );

	m_pSprite->Render(XGraphics::GetInstance()->GetDevice(), ALP_CUT, g_pCamera->GetViewMat(), g_pCamera->GetProjMat(), XMFLOAT4(255, 255, 255, 255));
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderBeginScene();
	XUserInterface::GetInstance()->DrawText(1, XMFLOAT4(100, 100, 200, 255), 0, 0, L"Main Menu");
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 50, L"Press START to Start New Game", 1);
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 100, L"Press BACK to Exit Game", 1);
	XUserInterface::GetInstance()->UIRenderEndScene();
#endif
}

void MainMenuState::Destroy()
{

}