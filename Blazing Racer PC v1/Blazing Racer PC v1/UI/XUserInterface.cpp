#include "stdafx.h"
#ifdef XBOX
#include "UI/XUserInterface.h"

XUserInterface* XUserInterface::ms_pXUserInterface = nullptr;

extern D3DDevice				*g_pd3dDevice;
extern D3DPRESENT_PARAMETERS	g_d3dpp;
extern TimeInfo					g_Time;

XUserInterface::~XUserInterface(void)
{
	Destroy();
}

void XUserInterface::Destroy()
{
	for(int i=0; i< m_hFonts.size(); i++)
		if(m_hFonts[i] != 0)
			XuiReleaseFont(m_hFonts[i]);

	if(m_hDC != 0 )
		XuiRenderDestroyDC(m_hDC);

	XuiRenderUninit();

	XuiUninit();
}


XUserInterface*	XUserInterface::GetInstance()
{
	if(ms_pXUserInterface == nullptr)
		ms_pXUserInterface = new XUserInterface();

	return ms_pXUserInterface;
}


void XUserInterface::InitXui()
{
	XUIInitParams initParams = { 0 };

	XUI_INIT_PARAMS( initParams );

	TypefaceDescriptor desc = { 0 };
	desc.szTypeface = L"Arial Unicode MS";
	desc.szLocator  = L"file://Game:/Content/Fonts/xarialuni.ttf";

	XuiRenderInitShared(g_pd3dDevice, &g_d3dpp, XuiD3DXTextureLoader);

	XuiRenderCreateDC(&m_hDC);

	XuiInit( &initParams );

	XuiRegisterTypeface( &desc, TRUE );

	//Set Animation Variables
	m_startTime	  = g_Time.fAppTime;
	m_alphaFactor = 255 * m_startTime;
}


void XUserInterface::CreateFont(float fontSize)
{
	HXUIFONT font;
	XuiCreateFont( L"Arial Unicode MS", fontSize, XUI_FONT_STYLE_NORMAL, 0, &font);
	m_hFonts.push_back(font);
}


void XUserInterface::Update()
{
	float dt = g_Time.fAppTime - m_startTime;
	m_alphaFactor = 255 *dt;

	if(m_alphaFactor >= 255)
	{
		m_startTime = g_Time.fAppTime;
		m_alphaFactor = 1;
	}
}

void XUserInterface::UIRenderBeginScene()
{
	XuiRenderBegin(m_hDC, D3DCOLOR_ARGB( 255, 0, 0, 100));

	D3DXMATRIX	matView;
	D3DXMatrixIdentity(&matView);
	XuiRenderSetViewTransform(m_hDC, &matView);
}


void XUserInterface::DrawText(int _fontTypeIndex, XMFLOAT4 color, float x, float y, LPCWSTR text)
{
	D3DCOLOR d3dColor = D3DCOLOR_ARGB((unsigned int)color.w, (unsigned int)color.x, (unsigned int)color.y, (unsigned int)color.z);

	XUIRect clipRect( 0, 0, SCREEN_WIDTH - x, SCREEN_HEIGHT - y );
	XuiMeasureText( m_hFonts[_fontTypeIndex], text, -1, XUI_FONT_STYLE_NORMAL, 0, &clipRect );

	// Set the text position in the device context
	D3DXMATRIX matXForm;
	D3DXMatrixIdentity( &matXForm );
	matXForm._41 = x;
	matXForm._42 = y;
	XuiRenderSetTransform( m_hDC, &matXForm );

	// Select the font and color into the device context
	XuiSelectFont( m_hDC, m_hFonts[_fontTypeIndex] );
	XuiSetColorFactor( m_hDC, ( DWORD )d3dColor );

	// Draw the text
	XuiDrawText( m_hDC, text, XUI_FONT_STYLE_LEFT_ALIGN, 0, &clipRect );
}

void XUserInterface::DrawAnimatedText(int _fontTypeIndex, XMFLOAT4 color, float x, float y, LPCWSTR text, float animSpeed)
{
	m_alphaFactor *= animSpeed;
	color.w		   = m_alphaFactor;

	DrawText(_fontTypeIndex, color, x, y, text);
}

void XUserInterface::UIRenderEndScene()
{
	XuiRenderEnd(m_hDC);
	XuiRenderPresent(m_hDC, NULL, NULL, NULL);
}

#endif