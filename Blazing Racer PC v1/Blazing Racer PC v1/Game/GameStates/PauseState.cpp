#include "stdafx.h"
#include "Game/GameStates/PauseState.h"
#include "Sound/XSound/XSound.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Util/Texture.h"
#include "Graphics/Camera.h"

using namespace GameState;
using namespace Graphics;
using namespace Util;

extern Camera*		g_pCamera;

PauseState::PauseState(void)
{
	m_isPaused	 = false;
}

PauseState::~PauseState(void)
{
}

void PauseState::Init()
{
	Texture *pTex = ResourceManager::GetInstance()->Load<Texture>("Game:\\Content\\Textures\\pause.jpg");
	m_pSprite = new XSprite();
	m_pSprite->InitSprite(-SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 720, 1280, pTex->GetTexture(), 1, false);
	//Update();
	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);
}

void PauseState::Update()
{
	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_BACK))
	{
		XSound::GetInstance()->PlayWave(WAVENAME_MENU_SCROLL_BLIP, 0, TRUE);
		GameHandler::GetInstance()->SetState(GAMESTATE_END, STATE_DESTROY);
	}

	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_B))
	{
		XSound::GetInstance()->PlayWave(WAVENAME_MENU_SCROLL_BLIP, 0, TRUE);
		GameHandler::GetInstance()->SetState(GAMESTATE_RUNNING, STATE_DESTROY);
	}

	if(InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_START))
	{
		XSound::GetInstance()->PlayWave(WAVENAME_MENU_SCROLL_BLIP, 0, TRUE);
		GameHandler::GetInstance()->SetState(GAMESTATE_MAINMENU, STATE_DESTROY);
	}

	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);

	m_pSprite->Update();
#ifdef XBOX
	XUserInterface::GetInstance()->Update();
#endif
}

void PauseState::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 
		D3DCOLOR_XRGB(0,255,255), 1.0f, 0L );

	m_pSprite->Render(XGraphics::GetInstance()->GetDevice(), ALP_CUT, g_pCamera->GetViewMat(), g_pCamera->GetProjMat(), XMFLOAT4(255, 255, 255, 255));
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderBeginScene();
	XUserInterface::GetInstance()->DrawText(1, XMFLOAT4(100, 100, 200, 255), 0, 0, L"Paused");
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 50, L"Press B to Resume", 1);
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 100, L"Press START to Quit to Main Menu", 1);
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(200, 100, 100, 255), 0, 150, L"Press BACK to Exit Game", 1);
	XUserInterface::GetInstance()->UIRenderEndScene();
#endif
}

void PauseState::Destroy()
{

}