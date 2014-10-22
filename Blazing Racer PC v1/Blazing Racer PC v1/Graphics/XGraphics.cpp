#include "stdafx.h"
#include "XGraphics.h"

D3DDevice				*g_pd3dDevice;
D3DPRESENT_PARAMETERS	g_d3dpp;
extern HWND				g_hMainWnd;

namespace Graphics
{

	XGraphics* XGraphics::m_pGraphicsInstance = nullptr;

	XGraphics::XGraphics(void)
	{
		m_pD3DDevice		= nullptr;
		m_bIsWideScreen		= false;
	}


	XGraphics::~XGraphics(void)
	{
		m_pD3DDevice->Release();
	}

	XGraphics* XGraphics::GetInstance()
	{
		if(!m_pGraphicsInstance)
		{
			m_pGraphicsInstance = new XGraphics();
		}

		return m_pGraphicsInstance;
	}

	HRESULT XGraphics::InitGraphics()
	{
		Direct3D* pD3D = Direct3DCreate9(D3D_SDK_VERSION);//Create DirectX 9 object.

		if(!pD3D)
			return E_FAIL;

		D3DPRESENT_PARAMETERS d3dParams;
		ZeroMemory(&d3dParams,sizeof(d3dParams));
#ifdef XBOX
		XVIDEO_MODE VideoMode;
		XGetVideoMode(&VideoMode);
		m_bIsWideScreen = VideoMode.fIsWideScreen;
		d3dParams.BackBufferWidth = min(VideoMode.dwDisplayHeight, 1280);
		d3dParams.BackBufferHeight = min(VideoMode.dwDisplayWidth, 720);
#else
		D3DMULTISAMPLE_TYPE mst = D3DMULTISAMPLE_8_SAMPLES;
		DWORD quality = 0;

		m_bIsWideScreen					= true;
		d3dParams.BackBufferWidth	    = 1280;
		d3dParams.BackBufferHeight		= 720;

		if (SUCCEEDED(pD3D->CheckDeviceMultiSampleType(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, true, mst, &quality)))
		{
			mst = D3DMULTISAMPLE_4_SAMPLES;
		}
		else
		{
			mst = D3DMULTISAMPLE_NONE;
			quality = 0;
		}
		d3dParams.MultiSampleType = mst;
		d3dParams.MultiSampleQuality = quality - 1;
		d3dParams.hDeviceWindow = g_hMainWnd;
		d3dParams.Flags = 0;
		d3dParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dParams.Windowed = true;
#endif
		d3dParams.BackBufferFormat		=	D3DFMT_X8R8G8B8;
		d3dParams.BackBufferCount		=	1;
		d3dParams.EnableAutoDepthStencil=	TRUE;
		d3dParams.AutoDepthStencilFormat=	D3DFMT_D24S8;
		d3dParams.SwapEffect			=	D3DSWAPEFFECT_DISCARD;
		d3dParams.PresentationInterval	=	D3DPRESENT_INTERVAL_ONE;

#ifdef XBOX
		if(FAILED(pD3D->CreateDevice(0,D3DDEVTYPE_HAL,NULL,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dParams,&m_pD3DDevice)))
			return E_FAIL;
#else
		if (FAILED(pD3D->CreateDevice(0, D3DDEVTYPE_HAL, g_hMainWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dParams, &m_pD3DDevice)))
			return E_FAIL;
#endif

		g_pd3dDevice = m_pD3DDevice;
		g_d3dpp		 = d3dParams;

		

#ifdef XBOX
		char *shaderPath = "Game:\\Content\\Shaders\\";
#else
		char shaderPath[] = "Content\\Shaders\\";
#endif
	
		//////////Init all the Shaders 
		XShader* pShader = new XShader();
		if (FAILED(pShader->InitShader("Content\\Shaders\\Color.vs", "Content\\Shaders\\Color.ps", m_pD3DDevice)))
			return E_FAIL;

		m_mShaderMap[COLOR_SHADER] = (IShaders*)pShader;

		XTexShader* pTShader = new XTexShader();
		if (FAILED(pTShader->InitShader("Content\\Shaders\\Tex.vs", "Content\\Shaders\\Tex.ps",m_pD3DDevice)))
			return E_FAIL;

		m_mShaderMap[TEX_SHADER] = (IShaders*)pTShader;

		XTexShader* pAShader = new XTexShader();
		if (FAILED(pAShader->InitShader("Content\\Shaders\\AlphaCut.vs", "Content\\Shaders\\AlphaCut.ps", m_pD3DDevice)))
			return E_FAIL;

		m_mShaderMap[ALP_CUT] = (IShaders*)pAShader;

		//pD3D->Release();

		return S_OK;
	}

	void XGraphics::Update()
	{

	}


	void XGraphics:: Render()
	{
		
	}

	void XGraphics::StartScene()
	{
		m_pD3DDevice->Clear(0L,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,D3DCOLOR_XRGB(0,200,25),1,0L);
	}

	void XGraphics::EndScene()
	{
		m_pD3DDevice->Present(NULL,NULL,NULL,NULL);
	}

	void XGraphics:: SetShader()
	{

	}	
}

