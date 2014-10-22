#pragma once
#ifndef __X_GRAPHICS_
#define __X_GRAPHICS_

#include <map>
#include "Graphics/IShaders.h"
#include "Graphics/XTexShader.h"
#include "Graphics/XShader.h"
#include "Util/Util.h"

#define SAFE_DELETE_POINTER(x) { if(x){ delete x; x = nullptr; } }
#define DegToRad(x) {x*57.3248f;}

using namespace Util;

namespace Graphics
{
	using namespace std;

	enum eSHADERS
	{
		COLOR_SHADER = 1,
		TEX_SHADER,
		ALP_CUT,

		MAX_SHADER
	};

	class XGraphics
	{
	private:
		static XGraphics*			m_pGraphicsInstance;

		D3DDevice*					m_pD3DDevice;
		BOOL						m_bIsWideScreen;

		map <eSHADERS,IShaders*>	m_mShaderMap;

		XGraphics(void);

	public:
		~XGraphics(void);
		static XGraphics*			GetInstance();

		HRESULT						InitGraphics();
		void						Update();
		void						Render();
		void						StartScene();
		void						EndScene();
		void						SetShader();

		D3DDevice*					GetDevice()					{return m_pD3DDevice;}
		IShaders*					GetShader(eSHADERS Shader)	{return m_mShaderMap[Shader];}

	};

}

#endif


