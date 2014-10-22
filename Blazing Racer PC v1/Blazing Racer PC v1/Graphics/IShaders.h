#pragma once
#ifndef __I_SHADER_
#define __I_SHADER_
#include "Util/ResourceManager.h"
#include "Util/TextFile.h"
#include "Util/Util.h"

using namespace Util;

namespace Graphics
{
	class IShaders
	{
	protected:
		D3DVertexShader*		m_pVertexShader;//Pointers to vertex and Pixel Shaders
		D3DPixelShader*			m_pPixelShader;

		D3DVertexBuffer*		m_pVertexBuffer;
		D3DVertexDeclaration*	m_pVertDec;

		const char*				strVertexShaderProgram;
		const char*				strPixelShaderProgram;


	public:
		IShaders(void);
		~IShaders(void);

		virtual HRESULT					InitShader(const char* vertexShader,const char* pixelShader,D3DDevice* pDevice) = 0;
		virtual D3DVertexShader*		GetVertexShader() {return m_pVertexShader;}//Get the pointers of the Shaders Created
		virtual D3DPixelShader*			GetPixelShader()  {return m_pPixelShader;}
		virtual D3DVertexDeclaration*	GetVertexDec()	  {return m_pVertDec;}

		virtual D3DVertexBuffer*		GetVertexBuffer() {return m_pVertexBuffer;}
		virtual UINT					GetStride() = 0;
	};


}

#endif
