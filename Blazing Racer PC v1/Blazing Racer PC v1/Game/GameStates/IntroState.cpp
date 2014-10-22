#include "stdafx.h"
#include "Game/GameStates/IntroState.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Util/Texture.h"
#include "Graphics/Camera.h"


using namespace GameState;
using namespace Graphics;
using namespace Util;

extern Camera*		g_pCamera;
extern TimeInfo		g_Time;

IntroState::IntroState(void)
{
	m_isPaused	 = false;
}

IntroState::~IntroState(void)
{

}

void IntroState::Init()
{
#ifdef XBOX
	Texture *pTex = ResourceManager::GetInstance()->Load<Texture>("Game:\\Content\\Textures\\intro.png");
#else
	Texture *pTex = ResourceManager::GetInstance()->Load<Texture>("Content\\Textures\\intro.png");
#endif
	m_pSprite = new XSprite();
	m_pSprite->InitSprite(-SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 720, 1280, pTex->GetTexture(), 1, false);
}

void IntroState::Update()
{
	if (InputManager::GetInstance()->GetKeyState(XINPUT_GAMEPAD_A) || GetAsyncKeyState(VK_UP))
	{
			GameHandler::GetInstance()->SetState(GAMESTATE_MAINMENU, STATE_DESTROY);
	}

	m_pSprite->Update();
#ifdef XBOX
	XUserInterface::GetInstance()->Update();
#endif
}

void IntroState::Render()
{
	XGraphics::GetInstance()->GetDevice()->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 
		D3DCOLOR_XRGB(0,25,255), 1.0f, 0L );

	m_pSprite->Render(XGraphics::GetInstance()->GetDevice(), ALP_CUT, g_pCamera->GetViewMat(), g_pCamera->GetProjMat(), XMFLOAT4(255, 255, 255, 255));
#ifdef XBOX
	XUserInterface::GetInstance()->UIRenderBeginScene();
	//XUserInterface::GetInstance()->DrawText(XMFLOAT4(m_alphaFactor, 100, 100, 100), 320, SCREEN_HEIGHT-100, L"Press A to Skip");
	XUserInterface::GetInstance()->DrawAnimatedText(0, XMFLOAT4(100, 100, 100, 255), 320, SCREEN_HEIGHT-100, L"Press A to Skip", 1);
	XUserInterface::GetInstance()->UIRenderEndScene();
#endif
}

void IntroState::Destroy()
{

}