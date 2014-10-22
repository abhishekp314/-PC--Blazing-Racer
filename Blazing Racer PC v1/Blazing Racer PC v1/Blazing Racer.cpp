// Blazing Racer v1.1 [X360].cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#ifdef XBOX
#include<xui.h>
#endif

#ifdef WIN32
#include "ApplicationFramework/d3dApp.h"
#endif

#include "Util/Util.h"
#include "Graphics/XGraphics.h"
#include "Graphics/XSprite.h"
#include "Graphics/Camera.h"
#include "Sound/XSound/XSound.h"
#include "UI/XUserInterface.h"
#include "Game/World.h"

using namespace Graphics;

extern Camera*		g_pCamera;

//-------------------------------------------------------------------------------------
// Name: main()
// Desc: The application's entry point
//-------------------------------------------------------------------------------------

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	D3DApp game(hInstance, "Blazing Racer", true);
	game.init();
	game.run();
}
#endif

#ifdef XBOX
void main()
{

	//Init the Time Variables
	InitTime();

	g_pCamera = new Camera();

	g_pCamera->InitCamera();
	g_pCamera->SetTarget(XMFLOAT3(0,0,1),1);

	// Initialize Direct3D
	if( FAILED( XGraphics::GetInstance()->InitGraphics() ) )
		return;

	//Init Sound
	XSound::GetInstance()->LoadWaveBank();

	//Init XUserInterface
	XUserInterface::GetInstance()->InitXui();
	XUserInterface::GetInstance()->CreateFont(12.0);
	XUserInterface::GetInstance()->CreateFont(18.0);
	XUserInterface::GetInstance()->CreateFont(8.0);

	GameHandler::GetInstance()->Init();

	while(!GameHandler::GetInstance()->GetGameExit()) // loop forever
	{
		//Update Time
		UpdateTime();

		// Update the world
		g_pCamera->Update();

		GameHandler::GetInstance()->Update();
		InputManager::GetInstance()->Update();

		//Put all rendering functions between these two 
		XGraphics::GetInstance()->StartScene();

		GameHandler::GetInstance()->Render();

		XGraphics::GetInstance()->EndScene();

		//Update XACT Engine
		XSound::GetInstance()->Update();
	}

	GameHandler::GetInstance()->Destroy();
	XUserInterface::GetInstance()->Destroy();
	XSound::GetInstance()->Destroy();
}

#endif