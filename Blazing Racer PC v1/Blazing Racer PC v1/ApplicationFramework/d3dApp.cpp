#include "stdafx.h"
#include "ApplicationFramework/d3dApp.h"
#include "Graphics/XGraphics.h"


#include "Util/Util.h"
#include "Graphics/XSprite.h"
#include "Graphics/Camera.h"
#include "Sound/XSound/XSound.h"
#ifdef XBOX
#include "UI/XUserInterface.h"
#endif
#include "Game/World.h"


using namespace Graphics;

IDirect3DDevice9* g_pD3DDevice = 0;
HINSTANCE		  g_hAppInstance = 0;
HWND			  g_hMainWnd = 0;

Camera*			  g_pCamera = nullptr;
TimeInfo		  g_Time;

extern TimeInfo	  g_Time;

//-------------------------------------------------------------------------------------
// Name: InitTime()
// Desc: Initializes the timer variables
//-------------------------------------------------------------------------------------
void InitTime()
{

	// Get the frequency of the timer
	LARGE_INTEGER qwTicksPerSec;
	QueryPerformanceFrequency(&qwTicksPerSec);
	g_Time.fSecsPerTick = 1.0f / (float)qwTicksPerSec.QuadPart;

	// Save the start time
	QueryPerformanceCounter(&g_Time.qwTime);

	// Zero out the elapsed and total time
	g_Time.qwAppTime.QuadPart = 0;
	g_Time.fAppTime = 0.0f;
	g_Time.fElapsedTime = 0.0f;
}



//-------------------------------------------------------------------------------------
// Name: UpdateTime()
// Desc: Updates the elapsed time since our last frame.
//-------------------------------------------------------------------------------------
void UpdateTime()
{
	LARGE_INTEGER qwNewTime;
	LARGE_INTEGER qwDeltaTime;

	QueryPerformanceCounter(&qwNewTime);
	qwDeltaTime.QuadPart = qwNewTime.QuadPart - g_Time.qwTime.QuadPart;

	g_Time.qwAppTime.QuadPart += qwDeltaTime.QuadPart;
	g_Time.qwTime.QuadPart = qwNewTime.QuadPart;

	g_Time.fElapsedTime = g_Time.fSecsPerTick * ((FLOAT)(qwDeltaTime.QuadPart));
	g_Time.fAppTime = g_Time.fSecsPerTick * ((FLOAT)(g_Time.qwAppTime.QuadPart));
}



namespace
{
	D3DApp *gd3dApp = 0;
}

LRESULT CALLBACK MainWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(gd3dApp!=0)
		return gd3dApp->msgProc(hwnd, msg,wParam,lParam);
	else
		return DefWindowProc(hwnd,msg,wParam,lParam);
}

D3DApp::D3DApp(HINSTANCE hInstance,std::string winCaption, bool enable4xMsaa)
{
	mMainWndCaption = winCaption;
	m_Enable4xMsaa = enable4xMsaa;
	m_clientWidth = 1280;
	m_clientHeight = 720;

	mhAppInst=hInstance;
	mhMainWnd=0;
	
	gd3dApp = this;
}

D3DApp::~D3DApp()
{
	GameHandler::GetInstance()->Destroy();
#ifdef XBOX
	XUserInterface::GetInstance()->Destroy();
#endif
	XSound::GetInstance()->Destroy();
}

HINSTANCE D3DApp::getAppInst()
{
	return mhAppInst;
}

HWND D3DApp::getMainWnd()
{
	return mhMainWnd;
}

void D3DApp::init()
{
	initMainWindow();
	//initDirect3D();

	//Init the Time Variables
	InitTime();

	g_pCamera = new Camera();

	g_pCamera->InitCamera();
	g_pCamera->SetTarget(XMFLOAT3(0, 0, 1), 1);

	// Initialize Direct3D
	if (FAILED(XGraphics::GetInstance()->InitGraphics()))
		return;

	//Init Sound
	XSound::GetInstance()->LoadWaveBank();

	//Init Input Manager
	InputManager::GetInstance()->Init();

#ifdef XBOX
	//Init XUserInterface
	XUserInterface::GetInstance()->InitXui();
	XUserInterface::GetInstance()->CreateFont(12.0);
	XUserInterface::GetInstance()->CreateFont(18.0);
	XUserInterface::GetInstance()->CreateFont(8.0);
#endif
	GameHandler::GetInstance()->Init();
}

void D3DApp::initMainWindow()
{
	WNDCLASS wc;
	wc.style=CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc=MainWndProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=mhAppInst;
	wc.hIcon=LoadIcon(0,IDI_APPLICATION);
	wc.hCursor=LoadCursor(0,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName=0;
	wc.lpszClassName="D3DWndClassName";

	if(!RegisterClass(&wc))
	{
		MessageBox(0,"Registering CLass failed",0,0);
		PostQuitMessage(0);
	}

	//Default to a window with a client area rectangle of 800x600

	RECT R={0, 0, m_clientWidth, m_clientHeight};
	AdjustWindowRect(&R,WS_OVERLAPPEDWINDOW,false);
	mhMainWnd=CreateWindow("D3DWndClassName",mMainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_clientWidth, m_clientHeight,
		0,0,mhAppInst,0);

	if(!mhMainWnd)
	{
		MessageBox(0,"Create Window Failed",0,0);
		PostQuitMessage(0);
	}
	g_hMainWnd = mhMainWnd;

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);
}


void D3DApp::initDirect3D()
{
	XGraphics::GetInstance()->InitGraphics();
}

int D3DApp::run()
{
	MSG msg = {0};

	__int64 cntsPerSec=0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt=1.0f/(float)cntsPerSec;

	__int64 prevTimeStamp=0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	while (msg.message != WM_QUIT || !GameHandler::GetInstance()->GetGameExit())
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//otherwise do animation/game stuffs
		else
		{
			//if app is paused; sleep
			if(mAppPaused)
			{
				Sleep(20);
				continue;
			}
			else
			{
				__int64 currTimeStamp=0;
				QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);

				float dt=(currTimeStamp-prevTimeStamp)*secsPerCnt;

				updateScene(dt);
				drawScene();

				prevTimeStamp=currTimeStamp;
			}
		}
	}
	return (int)msg.wParam;
}

void D3DApp::updateScene(float dt)
{
	//Update Time
	UpdateTime();

	// Update the world
	g_pCamera->Update();

	GameHandler::GetInstance()->Update();
	InputManager::GetInstance()->Update();

	//Update XACT Engine
	XSound::GetInstance()->Update();
}

void D3DApp::drawScene()
{
	//Put all rendering functions between these two 
	XGraphics::GetInstance()->StartScene();

	GameHandler::GetInstance()->Render();

	XGraphics::GetInstance()->EndScene();
}



LRESULT D3DApp::msgProc(HWND hwnd, UINT msg,WPARAM wParam,LPARAM lParam)
{
	//Is app in minimized or maximized state
	static bool minOrMaxed=false;

	RECT clientRect={0,0,0,0};

	switch(msg)
	{
		//WM_ACTIVE- is sent when windo is activated or deactivated
		//We pause the game when the main window is deactivated and 
		//unpause when it becomes active
	case WM_ACTIVATE:
					if(LOWORD(wParam)==WA_INACTIVE)
						mAppPaused=true;
					else
						mAppPaused=false;
					return 0;

// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	// Here we reset everything based on the new window dimensions.
	case WM_SIZE:

					return 0;
	case WM_ENTERSIZEMOVE:
					mAppPaused = true;

					return 0;
	case WM_EXITSIZEMOVE:
					GetClientRect(mhMainWnd,&clientRect);
					m_clientWidth = clientRect.right;
					m_clientHeight = clientRect.bottom;
					mAppPaused = false;
					onResize();
					
					return 0;
		// WM_CLOSE is sent when the user presses the 'X' button in the
	// caption bar menu.

	case WM_CLOSE:
					DestroyWindow(mhMainWnd);
					return 0;

	case WM_DESTROY:
					PostQuitMessage(0);
					return 0;
	case WM_KEYDOWN:
					if(wParam == VK_ESCAPE)
						enableFullScreenMode(false);
					else if(wParam == 'F')
						enableFullScreenMode(true);
					return 0;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

void D3DApp::onResize()
{

}

void D3DApp::enableFullScreenMode(bool enable)
{

}


bool D3DApp::isDeviceLost()
{
			return false;
}

