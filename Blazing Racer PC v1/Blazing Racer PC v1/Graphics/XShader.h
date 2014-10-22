#pragma once
#ifndef __X_SHADER_
#define __X_SHADER_

namespace Graphics
{
	class XShader
	{
	private:
		D3DVertexShader*		m_pVertexShader;//Pointers to vertex and Pixel Shaders
		D3DPixelShader*			m_pPixelShader;

		D3DVertexDeclaration*	m_pVertDec;
		int						a;
		string				strVertexShaderProgram;
		string				strPixelShaderProgram;

	public:
		XShader(void);
		~XShader(void);

		HRESULT					InitShader(const char* vertexShader,const char* pixelShader,D3DDevice* pDevice);
		D3DVertexShader*		GetVertexShader() {return m_pVertexShader;}//Get the pointers of the Shaders Created
		D3DPixelShader*			GetPixelShader()  {return m_pPixelShader;}
		D3DVertexDeclaration*	GetVertexDec()	  {return m_pVertDec;}
	};
}
#endif


