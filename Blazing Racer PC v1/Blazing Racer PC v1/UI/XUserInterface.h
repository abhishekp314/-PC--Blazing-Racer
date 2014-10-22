#pragma once

#ifndef __XUI__
#define __XUI__

#ifdef XBOX
#include<xui.h>


class XUserInterface
{
	static XUserInterface				*ms_pXUserInterface;
	HXUIDC								m_hDC;
	vector<HXUIFONT>					m_hFonts;
	float								m_alphaFactor;
	float								m_startTime;

	XUserInterface()
	{

	}

public:
	~XUserInterface(void);

	static XUserInterface*				GetInstance();
	void								InitXui();
	void								CreateFont(float fontSize);
	void								Destroy();
	void								Update();
	void								UIRenderBeginScene();
	void								UIRenderEndScene();
	void								DrawText(int _fontTypeIndex, XMFLOAT4 _color, float _x, float _y, LPCWSTR _text);
	void								DrawAnimatedText(int _fontTypeIndex, XMFLOAT4 _color, float _x, float _y, LPCWSTR _text, float _animSpeed);
};

#endif

#endif